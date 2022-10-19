/*
 * software_timer.c
 *
 *  Created on: Oct 4, 2022
 *      Author: ttrng
 */

#include "software_timer.h"


Software_Timer timerOne;
Software_Timer timerTwo;

static void SOFT_TIM1_Init(void){
	timerOne.division 	= FULL;
	timerOne.counter 	= TIMER_DELAY/(TIMER_INTERRUPT_TIM2 * timerOne.division);
	timerOne.flag		= 0;
}
static void SOFT_TIM2_Init(void){
	timerTwo.division 	= HALF;
	timerTwo.counter 	= TIMER_DELAY/(TIMER_INTERRUPT_TIM2 * timerTwo.division);
	timerTwo.flag		= 0;
}
static void Counter_Update(Software_Timer* softTimer){
	if (softTimer->counter > 0){
		softTimer->counter--;
		if (softTimer->counter <= 0){
			softTimer->flag = 1;
		}
	}
}
void Set_Timer(void){
	SOFT_TIM1_Init();
	SOFT_TIM2_Init();
}
void Timer_Run(void){
	Counter_Update(&timerOne);
	//Counter_Update(&timerTwo);
}
int Flag_Status(){
	if(timerTwo.flag == 1){
		return timerTwo.flag;
	}
	return timerOne.flag;
}
