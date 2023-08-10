/*
 * uart.h
 *
 *  Created on: Aug 1, 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32f4xx.h"

void USART3_UART_TX_Init(void);
void USART3_UART_RX_Init(void);

int __io_putchar(int ch);

#endif /* INC_UART_H_ */
