/*
 * exti.h
 *
 *  Created on: Aug 1, 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#ifndef INC_EXTI_H_
#define INC_EXTI_H_

#include "stm32f4xx_hal.h"

void pc13_exti_init(void);
void gpio_init(void);
uint8_t read_sensor_status(void);

#endif /* INC_EXTI_H_ */
