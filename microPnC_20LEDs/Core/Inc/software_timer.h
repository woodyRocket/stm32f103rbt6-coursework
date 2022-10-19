/*
 * software_timer.h
 *
 *  Created on: Oct 4, 2022
 *      Author: ttrng
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define TIMER_DELAY							500
#define TIMER_INTERRUPT_TIM2				10
#define TIMER_INTERRUPT_TIM4				50

enum TYPE{
	FULL 			= 1,
	HALF 			= 2,
	THIRD 			= 3,
	QUARTER 		= 4,
	FIFTH 			= 5,
	SIXTH			= 6,
	SEVENTH			= 7,
	EIGHTH			= 8,
	NINTH			= 9,
	TENTH			= 10
};

typedef struct __SOFTWARE_TIM {
	enum TYPE division;
	int counter;
	int flag;
}Software_Timer;

void Set_Timer(void);
void Timer_Run(void);
int Flag_Status(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
