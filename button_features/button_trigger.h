/*
 * button_trigger.h
 *
 *  Created on: Oct 4, 2022
 *      Author: ttrng
 */

#ifndef INC_BUTTON_TRIGGER_H_
#define INC_BUTTON_TRIGGER_H_

#include <stdint.h>

#define BUTTON_PRESSED 		0
#define BUTTON_UNPRESSED 	1

typedef enum ButtonStatus = {UNPRESSED, PRESSED} buttonState;

buttonState = UNPRESSED;

uint8_t Button_Is_Pressed(void);
uint8_t Button_Is_Unpressed(void);
void Button_Trigger(void);

#endif /* INC_BUTTON_TRIGGER_H_ */
