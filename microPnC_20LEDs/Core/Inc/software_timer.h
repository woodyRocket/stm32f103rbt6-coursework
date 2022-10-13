/*
 * software_timer.h
 *
 *  Created on: Oct 4, 2022
 *      Author: ttrng
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define TIMER_DELAY					50
#define TIMER_INTERRUPT				10

extern int timerFlag;

void Set_Timer(void);
void Timer_Run(void);


#endif /* INC_SOFTWARE_TIMER_H_ */
