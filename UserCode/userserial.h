/*
 * userserial.h
 *
 *  Created on: Dec 25, 2024
 *      Author: Delta
 */

#ifndef USERCODE_USERSERIAL_H_
#define USERCODE_USERSERIAL_H_

#include "F28x_Project.h"
#include "F2837xD_device.h"
#include "F2837xD_Examples.h"

#include "driverlib.h"
#include "device.h"

#define BUFFER_SIZE 128


void UART_GPIO_init(uint32_t base);
void UART_init(uint32_t base, uint32_t baud);
void Send_Serial(uint32_t base, const uint16_t *data, uint16_t length);
int Recive_Serial(uint32_t base,uint16_t *data);
__interrupt void scicRxISR(void);

#endif /* USERCODE_USERSERIAL_H_ */
