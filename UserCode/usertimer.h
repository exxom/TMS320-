/*
 * usertimer.h
 *
 *  Created on: Dec 25, 2024
 *      Author: Delta
 */

#ifndef USERCODE_USERTIMER_H_
#define USERCODE_USERTIMER_H_

#include "device.h"
#include "driverlib.h"

void CPU_Timers_Init(uint32_t timerbase);
void CPU_Timers_Config(uint32_t cpuTimer, float freq, float period);
__interrupt void cpuTimer0ISR(void);

#endif /* USERCODE_USERTIMER_H_ */
