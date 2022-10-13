/*
 * support_function.h
 *
 *  Created on: Oct 4, 2022
 *      Author: ttrng
 */

#ifndef INC_BUFFER_MANIP_H_
#define INC_BUFFER_MANIP_H_

#include <stdint.h>
#include <stdlib.h>

#define LED_ON 									1
#define LED_OFF									0
#define NUMBER_OF_LED_TYPE						2
#define SPACE_BETWEEN_SAME_LED 					2
#define NUMBER_OF_LED_STATE						2

uint8_t Get_Bit_Value(uint8_t data, uint8_t index);
uint8_t** Create_Copy_Buffer(uint8_t* buffer, uint8_t size, uint8_t numberCopy);
void Free_Copy_Buffer(uint8_t** multipleBuffer, uint8_t numberCopy);
void Update_Red_Index(uint8_t size);
void Update_Green_Index(uint8_t size);
void Rollback_Green_Index(uint8_t size);
void Rollback_Red_Index(uint8_t size);
//uint8_t Toggle_Led(uint8_t status);
void Toggle_Led(uint8_t* status);
uint8_t* Single_Led_Blink(uint8_t* buffer, uint8_t size);
uint8_t* All_Led_On(uint8_t* buffer, uint8_t size);
uint8_t* All_Red_On(uint8_t* buffer, uint8_t size);
uint8_t* All_Green_On(uint8_t* buffer, uint8_t size);
uint8_t* All_Red_Blink(uint8_t* buffer, uint8_t size);
uint8_t* All_Green_Blink(uint8_t* buffer, uint8_t size);
uint8_t* Green_Moving_Forward(uint8_t* buffer, uint8_t size);
uint8_t* Red_Moving_Forward(uint8_t* buffer, uint8_t size);
uint8_t* Green_Moving_Backward(uint8_t* buffer, uint8_t size);
uint8_t* Red_Moving_Backward(uint8_t* buffer, uint8_t size);
uint8_t* Red_Backward_Green_Forward(uint8_t* buffer, uint8_t size);
uint8_t* Red_Forward_Green_Backward(uint8_t* buffer, uint8_t size);
uint8_t* Red_Backward_Green_Backward(uint8_t* buffer, uint8_t size);
uint8_t* Red_Forward_Green_Forward(uint8_t* buffer, uint8_t size);
uint8_t* Red_Moving_Middle(uint8_t* buffer, uint8_t size);
uint8_t* Green_Moving_Middle(uint8_t* buffer, uint8_t size);
uint8_t* All_Led_Moving_Middle(uint8_t* buffer, uint8_t size);
uint8_t* Red_Cummulative_Forward(uint8_t* buffer, uint8_t size);
uint8_t* Red_Cummulative_Backward (uint8_t* buffer, uint8_t size);
uint8_t* Green_Cummulative_Forward(uint8_t* buffer, uint8_t size);
uint8_t* Green_Cummulative_Backward (uint8_t* buffer, uint8_t size);
uint8_t* Red_Forward_Green_Backward_Cumm(uint8_t* buffer, uint8_t size);
#endif /* INC_BUFFER_MANIP_H_ */
