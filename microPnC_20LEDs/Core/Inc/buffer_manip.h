/*
 * support_function.h
 *
 *  Created on: Oct 4, 2022
 *      Author: ttrng
 */

#ifndef INC_BUFFER_MANIP_H_
#define INC_BUFFER_MANIP_H_

#include <stdint.h>

#define LED_ON 					1
#define LED_OFF					0
#define SPACE_BETWEEN_SAME_LED 	2

uint8_t Get_Bit_Value(uint8_t data, uint8_t index);
void Single_Led_Blink(uint8_t* buffer, uint8_t size);
void All_Red_On(uint8_t* buffer, uint8_t size);
void All_Green_On(uint8_t* buffer, uint8_t size);
void All_Red_Blink(uint8_t* buffer, uint8_t size);
void All_Green_Blink(uint8_t* buffer, uint8_t size);
void Green_Moving_Forward (uint8_t* buffer, uint8_t size);
void Red_Moving_Forward (uint8_t* buffer, uint8_t size);
void Green_Moving_Backward (uint8_t* buffer, uint8_t size);
void Red_Moving_Backward (uint8_t* buffer, uint8_t size);

#endif /* INC_BUFFER_MANIP_H_ */
