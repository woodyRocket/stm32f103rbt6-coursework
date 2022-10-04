/*
 * software_timer.h
 *
 *  Created on: Oct 4, 2022
 *      Author: ttrng
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define TIMER_DELAY				500
#define TIMER_INTERRUPT			10

extern int timerFlag;

void setTimer(void);
void timerRun(void);


#endif /* INC_SOFTWARE_TIMER_H_ */
