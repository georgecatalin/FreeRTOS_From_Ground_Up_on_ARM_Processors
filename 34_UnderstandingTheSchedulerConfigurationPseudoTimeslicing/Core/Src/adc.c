/*
 * adc.c
 *
 *  Created on: Aug 1, 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#include "adc.h"

void adc2_init(void)
{
	/* ******************************************************************************************
	 * ADC stands for analog to digital conversion
	 * We are going to use for this example ADC1 with channel 1 which points to pin PA1
	 * **************************************************************************************  */

	// Enable clock access from GPIOA to AHB1 Advanced High Performance Bus
	RCC->AHB1ENR |=(1UL<<0);

	// Enable clock access from ADC1 to APB2 Advanced Performance Bus
	RCC->APB2ENR |= (1UL<<8);

	//Configure the mode of PA1 to analog
	GPIOA->MODER |= (1UL<<3);
	GPIOA->MODER |= (1UL<<2);


	//Enable ADC

	//Trigger off by the software
	ADC1->CR2 = 0;

	//Set the conversion the channel 2
	ADC1->SQR3 = 1;

	ADC1->SQR1 = 0;

	//Trigger on ADC BY software
	ADC1->CR2 |= 1;
}



uint32_t read_adc_sensor_data(void)
{
	//Start the conversion
	ADC1->CR2 |= (1UL<<30);

	//Wait until the conversion is finished
	while(!(ADC1->SR & (1UL<<1))){}

	//Return converted data
	return (ADC1->DR);
}

