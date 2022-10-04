/*
 * software_timer.c
 *
 *  Created on: Oct 4, 2022
 *      Author: ttrng
 */

#include "software_timer.h"

int timerCounter 	= 0;
int timerFlag 		= 0;

void setTimer(void){
	timerCounter = TIMER_DELAY/TIMER_INTERRUPT;
	timerFlag 	 = 0;
}
void timerRun(void){
	if (timerCounter > 0){
		timerCounter--;
		if (timerCounter <= 0){
			timerFlag = 1;
		}
	}
}
