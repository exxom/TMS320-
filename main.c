/*
 * main.c
 *
 *  Created on: 09-Dec-2021
 *      Author: Admin
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "F28x_Project.h"
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

#include "device.h"
#include "driverlib.h"

#include "usergpio.h"
#include "userserial.h"
#include "usertimer.h"

#define BUFFER_SIZE 128
Uint16 len; // Used for checking the received data
char rdata[BUFFER_SIZE];

uint8_t ledG, ledR;

#define ON 1
#define OFF 0

__interrupt void scicRxISR(void);
__interrupt void cpuTimer0ISR(void);

uint16_t timer;

void main(void)
{
    Device_init();
    Device_initGPIO();

    DINT;

    UART_GPIO_init(SCIC_BASE);
    UART_init(SCIC_BASE, 9600);

    Interrupt_initModule();
    Interrupt_initVectorTable();
    IER = 0x0000;
    IFR = 0x0000;

    Interrupt_register(INT_SCIC_RX, scicRxISR);

    Interrupt_enable(INT_SCIC_RX);

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);

    Interrupt_register(INT_TIMER0, &cpuTimer0ISR);
    CPU_Timers_Init(CPUTIMER0_BASE);
    CPU_Timers_Config(CPUTIMER0_BASE, DEVICE_SYSCLK_FREQ, 200000);
    Interrupt_enable(INT_TIMER0);

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

    GPIO_init_Pin();

    EINT;

    CPUTimer_startTimer(CPUTIMER0_BASE);

    while (1)
    {
        if (rdata[len - 1] == '\n')
        {
           Send_Serial(SCIC_BASE, (uint16_t*) rdata, len);
            if (rdata[0] == '#')
            {
                if (strstr(rdata, "onG"))
                {
                    ledG = ON;
                }
                if (strstr(rdata, "offG"))
                {
                    ledG = OFF;
                }
                if (strstr(rdata, "onR"))
                {
                    ledR = ON;
                }
                if (strstr(rdata, "offR"))
                {
                    ledR = OFF;
                }
            }
            memset(rdata, '\0', 128);
            len = 0;
        }
        if (timer > 2)
        {
            timer = 0;
            if (ledG == ON)
            {
                GPIO_togglePin(123);
            }
            if (ledR == ON)
            {
                GPIO_togglePin(32);
            }
            if (ledG == OFF)
            {
                GPIO_writePin(123, 0);
            }
            if (ledR == OFF)
            {
                GPIO_writePin(32, 0);
            }
        }
    }

}

__interrupt void scicRxISR(void)
{

    rdata[len] = ScicRegs.SCIRXBUF.all;
    len++;

    if (len >= BUFFER_SIZE)
        len = 0;

    PieCtrlRegs.PIEACK.all |= 0x100;       // Issue PIE ack
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP8);
}

__interrupt void cpuTimer0ISR(void)
{
    timer++;

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

