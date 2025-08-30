/*
 * uart.h
 *
 *  Created on: Aug 24, 2025
 *      Author: Engr. Moneeb
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx.h"

void system_uart_init(void);
#define SR_RXNE (1U<<5) //Static Rx Interrupt register

#endif /* UART_H_ */
