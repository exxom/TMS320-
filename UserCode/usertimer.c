/*
 * usertimer.c
 *
 *  Created on: Dec 25, 2024
 *      Author: Delta
 */

#include "usertimer.h"

void CPU_Timers_Init(uint32_t timerbase)
{
    CPUTimer_setPeriod(timerbase, 0xFFFFFFFF);
    CPUTimer_setPreScaler(timerbase, 0);
    CPUTimer_stopTimer(timerbase);
    CPUTimer_reloadTimerCounter(timerbase);
}

void CPU_Timers_Config(uint32_t cpuTimer, float freq, float period)
{
    uint32_t temp;

    temp = (uint32_t) (freq / 1000000 * period);
    CPUTimer_setPeriod(cpuTimer, temp);
    CPUTimer_setPreScaler(cpuTimer, 0);
    CPUTimer_stopTimer(cpuTimer);
    CPUTimer_reloadTimerCounter(cpuTimer);
    CPUTimer_setEmulationMode(cpuTimer,
                              CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
    CPUTimer_enableInterrupt(cpuTimer);
}
