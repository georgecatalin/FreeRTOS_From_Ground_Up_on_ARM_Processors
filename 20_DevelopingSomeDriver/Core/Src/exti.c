/*
 * exti.c
 *
 *  Created on: Aug 1, 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#include "exti.h"

#define GPIOC_ENR  (1UL<<2) //this info is taken from RM0090: RCC AHB1 peripheral clock register (RCC_AHB1ENR)
#define SYSCFG_EN (1UL<<14) //this info is taken from RM0090: RCC APB2 peripheral clock enable register (RCC_APB2ENR)

void pc13_exti_init(void)
{

	/* optional, but good practice: Disable global interrupt */
	__disable_irq();

	/* Enable clock access for GPIOC */
	RCC->AHB1ENR |= GPIOC_ENR;

	/* Set PC13 as Input Pin , even this is the default mode we need to be explicit about it */
	GPIOC->MODER &= ~(1<<27); // '0' from RM0090: GPIO port mode register (GPIOx_MODER) (x = A..I/J/K)
	GPIOC->MODER &= ~(1<<26); // '0' from RM0090: GPIO port mode register (GPIOx_MODER) (x = A..I/J/K)

	/* Enable clock access to SYSCFG */
	RCC->APB2ENR |= SYSCFG_EN;

	/* Select port C for EXTI13 */
    SYSCFG->EXTICR[3] |= (1UL<<5); // EXTICR[3] = EXTICR4

    /* Unmask EXTI13 with IMR */
    EXTI->IMR |= (1UL<<13);

    /* Select falling edge trigger */
    EXTI->FTSR |= (1UL<<13);

    /*  set the priority of the interrupt associated with the EXTI (External Interrupt) lines 15 to 10 */
    NVIC_SetPriority(EXTI15_10_IRQn,6);

    /* Enable EXTI  in the NVIC Nested Vector Interrupt Controller for the group of lines 15 till 10 */
    NVIC_EnableIRQ(EXTI15_10_IRQn); // EXTI15_10_IRQn refers to the group of external interrupt lines 15 to 10.

	/* Enable  global Interrupts */
	__enable_irq();

}

void gpio_init(void)
{
	//enable clock access to GPIO C
	RCC->AHB1ENR = (1Ul<<2);

	//set Pin C13 Mode to input -> As default is 0x0000 0000 for other ports there is no need to do anything

}

uint8_t read_sensor_status(void)
{
	//we use GPIO INPUT DATA REGISTER for PC13
	if(GPIOC->IDR & (1UL<<13))
	{
		return 1; // it depends on the MCU, either pressed or not pressed -> on the NUCLEO F429ZI button is pressed
	}
	else
	{
		return 0; // it depends on the MCU, viceversa of previous state  -> on the NUCLEO F429ZI button is NOT pressed
	}
}
