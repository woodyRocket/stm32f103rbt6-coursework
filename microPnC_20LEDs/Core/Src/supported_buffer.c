/*
 * support_function.c
 *
 *  Created on: Oct 4, 2022
 *      Author: ttrng
 */

#include "supported_buffer.h"

static uint8_t ledIndex = 0;

void Single_Led_Blink(uint8_t* buffer, uint8_t size){
//	switch(ledIndex){
//	case 0:
//		ledDriverBuffer[ledIndex] = 1;
//		ledDriverBuffer[NUMBER_OF_LED - 1] = 0;
//		break;
//	case 1:
//		ledDriverBuffer[ledIndex] = 1;
//		ledDriverBuffer[ledIndex-1] = 0;
//		break;
//	default:
//		ledDriverBuffer[ledIndex] 	=  (ledIndex + 1) % ledIndex;
//		ledDriverBuffer[ledIndex-1] = 0;
//		break;
//	}
//	ledIndex = (ledIndex + 1) % NUMBER_OF_LED;
	uint8_t bIndex;
	buffer[ledIndex] 	=  1;
	for (bIndex = 0; bIndex < size; bIndex++){
		if (bIndex != ledIndex){
			buffer[bIndex] = 0;
		}
	}
	ledIndex = (ledIndex + 1) % size;
}

void All_Led_Blink(uint8_t* buffer, uint8_t size){
	uint8_t bIndex;
	for (bIndex = 0; bIndex < size; bIndex++){
		if (bIndex % 2 == 0){
			buffer[bIndex] = 1;
		}
	}
	for (ledIndex = 0; ledIndex < size; ledIndex++){
		buffer[(ledIndex + 1) % size] = (buffer[(ledIndex + 1) % size] + 1) % 2;
	}
}
