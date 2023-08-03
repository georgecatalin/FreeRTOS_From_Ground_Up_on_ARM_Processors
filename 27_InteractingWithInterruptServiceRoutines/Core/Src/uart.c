/*
 * uart.c
 *
 *  Created on: Aug 1, 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#include "uart.h"

UART_HandleTypeDef huart3;

int uart3_write(int ch)
{
	while(!(USART3->SR & USART_SR_TXE))
	{

	}

	USART3->DR = (ch & 0xFF); // 0xFF = 1111 1111
	return ch;
}

int uart3_read(void)
{
	while(!(USART3->SR & (1UL<<5))){}
	return (USART3->DR);
}

int __io_putchar(int ch)
{
	uart3_write(ch);
	return ch;
}

void USART3_UART_TX_Init(void)
{
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    //
  }

}

void USART3_UART_RX_Init(void)
{
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    //Error_Handler();
  }

}
