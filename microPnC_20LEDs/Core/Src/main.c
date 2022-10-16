/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#include "buffer_manip.h"
#include "software_timer.h"
//#include "button_trigger.h"
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define RELAY			 			PD2
#define LED_SDI 					PC6
#define LED_OE 						PC5
#define LED_CLK 					PC3
#define LED_LE 						PC4
#define PRO_VER						PB2

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define NUMBER_OF_LED				20
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
static uint8_t ledDriverBuffer[NUMBER_OF_LED] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
static void Relay_Enable(void);
static void Latch_Enable(void);
static void Latch_Disable(void);
static void Output_Enable(void);
//static void Output_Disable(void);
static void Clock_On(uint8_t count);
static void Clock_Off(uint8_t count);
static void Data_Out(GPIO_PinState state);
//uint8_t Get_Bit_Value(uint8_t data, uint8_t index);
void Led_Display(void);
void Update_Led_Driver_Buffer(void);
void Button_Input(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  Output_Enable();
  Relay_Enable();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  Set_Timer();
  while (1)
  {
	  if (timerFlag == 1){
		  Set_Timer();
		  Update_Led_Driver_Buffer();
		  Led_Display();
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
static void Relay_Enable(void){
	HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, RESET);
}
static void Latch_Enable(void){
	HAL_GPIO_WritePin(LED_LE_GPIO_Port, LED_LE_Pin, GPIO_PIN_RESET);
}
static void Latch_Disable(void){
	HAL_GPIO_WritePin(LED_LE_GPIO_Port, LED_LE_Pin, GPIO_PIN_SET);
}
static void Output_Enable(void){
	HAL_GPIO_WritePin(LED_OE_GPIO_Port, LED_OE_Pin, GPIO_PIN_SET);
}
//static void Output_Disable(void){
//	HAL_GPIO_WritePin(LED_OE_GPIO_Port, LED_OE_Pin, GPIO_PIN_RESET);
//}
static void Clock_On(uint8_t count){
	if (count <= 0) return;
	while (count-- != 0) {
		HAL_GPIO_WritePin(LED_CLK_GPIO_Port, LED_CLK_Pin, GPIO_PIN_RESET);
	}
}
static void Clock_Off(uint8_t count){
	if (count <= 0) return;
	while (count-- != 0) {
		HAL_GPIO_WritePin(LED_CLK_GPIO_Port, LED_CLK_Pin, GPIO_PIN_SET);
	}

}
static void Data_Out(GPIO_PinState state){
	HAL_GPIO_WritePin(LED_SDI_GPIO_Port, LED_SDI_Pin, state);
}

void Led_Display(void){
	Latch_Disable();
	for (uint8_t iter = 0; iter < NUMBER_OF_LED; iter++){
		Clock_Off(1);
		Data_Out(ledDriverBuffer[iter]);
		Clock_On(10);
	}
	Latch_Enable();
}
void Update_Led_Driver_Buffer(void){
	//Single_Led_Blink(ledDriverBuffer, NUMBER_OF_LED);
	//All_Led_On(ledDriverBuffer, NUMBER_OF_LED);
	//All_Red_On(ledDriverBuffer, NUMBER_OF_LED);
	//All_Green_On(ledDriverBuffer, NUMBER_OF_LED);
	//All_Red_Blink(ledDriverBuffer, NUMBER_OF_LED);
	//All_Green_Blink(ledDriverBuffer, NUMBER_OF_LED);
	//Red_Moving_Forward(ledDriverBuffer, NUMBER_OF_LED);
	//Green_Moving_Forward(ledDriverBuffer, NUMBER_OF_LED);
	//Green_Moving_Backward(ledDriverBuffer, NUMBER_OF_LED);
	//Red_Moving_Backward(ledDriverBuffer, NUMBER_OF_LED);
	//Red_Backward_Green_Forward(ledDriverBuffer, NUMBER_OF_LED);
	//Red_Forward_Green_Backward(ledDriverBuffer, NUMBER_OF_LED);
	//All_Led_Moving_Backward(ledDriverBuffer, NUMBER_OF_LED);
	//All_Led_Moving_Forward(ledDriverBuffer, NUMBER_OF_LED);
	//Red_Moving_Middle(ledDriverBuffer, NUMBER_OF_LED);
	//Green_Moving_Middle(ledDriverBuffer, NUMBER_OF_LED);
	//All_Led_Moving_Middle(ledDriverBuffer,NUMBER_OF_LED);
	//Red_Cummulative_Forward(ledDriverBuffer, NUMBER_OF_LED);
	//Red_Cummulative_Backward(ledDriverBuffer, NUMBER_OF_LED);
	//Green_Cummulative_Forward(ledDriverBuffer, NUMBER_OF_LED);
	//Green_Cummulative_Backward(ledDriverBuffer, NUMBER_OF_LED);
	//Red_Forward_Green_Backward_Cumm(ledDriverBuffer, NUMBER_OF_LED);
	//Red_Backward_Green_Forward_Cumm(ledDriverBuffer, NUMBER_OF_LED);
	//All_Led_Cummulative_Forward(ledDriverBuffer, NUMBER_OF_LED);
	//All_Led_Cummulative_Backward(ledDriverBuffer, NUMBER_OF_LED);
	Half_Mixing_Alternative(ledDriverBuffer, NUMBER_OF_LED);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	Timer_Run();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
