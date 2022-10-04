/*
 * button_trigger.c
 *
 *  Created on: Oct 4, 2022
 *      Author: ttrng
 */


#include "button_trigger.h"

static uint8_t buttonStatus = 0;
static uint8_t count 		= 0;

uint8_t Button_Is_Pressed(void){
	if (buttonStatus = BUTTON_PRESSED)
		return 1;
	return 0;
}

uint8_t Button_Is_Unpressed(void){
	if (buttonStatus == BUTTON_UNPRESSED)
		return 1;
	return 0;
}

void Button_Trigger(void){
	switch(buttonState){
	case UNPRESSED:
		if(Button_Is_Pressed()){
			count++;
			buttonState = PRESSED;
		}
		break;
	case PRESSED:
		if(Button_Is_Unpressed()){
			buttonState = UNPRESSED;
		}
		break;
	}
	default:
		break;

}
