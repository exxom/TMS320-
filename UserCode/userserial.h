/*
 * userserial.h
 *
 *  Created on: Dec 25, 2024
 *      Author: Delta
 */

#ifndef USERCODE_USERSERIAL_H_
#define USERCODE_USERSERIAL_H_

#include "driverlib.h"
#include "device.h"

void UART_GPIO_init(uint32_t base);
void UART_init(uint32_t base, uint32_t baud);
void Send_Serial(uint32_t base, const uint16_t *data, uint16_t length);
int Recive_Serial(uint32_t base,uint16_t *data);

#endif /* USERCODE_USERSERIAL_H_ */
