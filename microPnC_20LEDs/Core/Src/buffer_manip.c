/*
 * support_function.c
 *
 *  Created on: Oct 4, 2022
 *      Author: ttrng
 */

#include <buffer_manip.h>

static uint8_t ledRedIndex 		= 0;
static uint8_t ledGreenIndex 	= 1;

uint8_t Get_Bit_Value(uint8_t data, uint8_t index){
	return (data >> index) & 0x01;
}

void Single_Led_Blink(uint8_t* buffer, uint8_t size){
	uint8_t bIndex;
	buffer[ledRedIndex] 	=  LED_ON;
	for (bIndex = 0; bIndex < size; bIndex++){
		if (bIndex != ledRedIndex){
			buffer[bIndex] = LED_OFF;
		}
	}
	ledRedIndex = (ledRedIndex + 1) % size;
}

void All_Red_On(uint8_t* buffer, uint8_t size){
	for (ledRedIndex = 0; ledRedIndex < size; ledRedIndex = ledRedIndex + SPACE_BETWEEN_SAME_LED){
		buffer[ledRedIndex] = LED_ON;
	}
}
void All_Green_On(uint8_t* buffer, uint8_t size){
	for (ledGreenIndex = 1; ledGreenIndex < size; ledGreenIndex = ledGreenIndex + SPACE_BETWEEN_SAME_LED){
		buffer[ledGreenIndex] = LED_ON;
	}
}
void All_Red_Blink(uint8_t* buffer, uint8_t size){
	for (ledRedIndex = 0; ledRedIndex < size; ledRedIndex = ledRedIndex + SPACE_BETWEEN_SAME_LED){
		buffer[ledRedIndex] = (buffer[ledRedIndex] + 1) % 2;
	}
}
void All_Green_Blink(uint8_t* buffer, uint8_t size){
	for (ledGreenIndex = 1; ledGreenIndex < size; ledGreenIndex = ledGreenIndex + SPACE_BETWEEN_SAME_LED){
		buffer[ledGreenIndex] = (buffer[ledGreenIndex] + 1) % 2;
	}
}
void Green_Moving_Forward (uint8_t* buffer, uint8_t size){
	uint8_t bIndex;
	buffer[ledGreenIndex] 	=  LED_ON;
	for (bIndex = 0; bIndex < size; bIndex++){
		if (bIndex != ledGreenIndex){
			buffer[bIndex] = LED_OFF;
		}
	}
	ledGreenIndex = (ledGreenIndex + SPACE_BETWEEN_SAME_LED) % size;
}
void Red_Moving_Forward (uint8_t* buffer, uint8_t size){
	uint8_t bIndex;
	buffer[ledRedIndex] 	=  LED_ON;
	for (bIndex = 0; bIndex < size; bIndex++){
		if (bIndex != ledRedIndex){
			buffer[bIndex] = LED_OFF;
		}
	}
	ledRedIndex = (ledRedIndex + SPACE_BETWEEN_SAME_LED) % size;
}
void Green_Moving_Backward (uint8_t* buffer, uint8_t size){
	uint8_t bIndex;
	uint8_t reverseIndex = size - ledGreenIndex;
	buffer[reverseIndex] 	=  LED_ON;
	for (bIndex = 0; bIndex < size; bIndex++){
		if (bIndex != reverseIndex){
			buffer[bIndex] = LED_OFF;
		}
	}
	ledGreenIndex = (ledGreenIndex + SPACE_BETWEEN_SAME_LED) % size;
}
void Red_Moving_Backward (uint8_t* buffer, uint8_t size){
	uint8_t bIndex;
	uint8_t reverseIndex = size - ledRedIndex - SPACE_BETWEEN_SAME_LED;
	buffer[reverseIndex] 	=  LED_ON;
	for (bIndex = 0; bIndex < size; bIndex++){
		if (bIndex != reverseIndex){
			buffer[bIndex] = LED_OFF;
		}
	}
	ledRedIndex = (ledRedIndex + SPACE_BETWEEN_SAME_LED) % size;
}
