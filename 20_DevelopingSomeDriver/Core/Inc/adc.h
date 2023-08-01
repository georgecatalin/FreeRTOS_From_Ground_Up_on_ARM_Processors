/*
 * adc.h
 *
 *  Created on: Aug 1, 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "stm32f4xx.h"

// I intend to use ADC2 with channel 2 -> corresponds to PINA2  (or ADC1 channel 1 -> corresponds to PA1)

void adc2_init(void);
uint32_t read_adc_sensor_data(void);

#endif /* INC_ADC_H_ */
