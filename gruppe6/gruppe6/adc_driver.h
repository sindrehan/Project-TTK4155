/*
 * adc_driver.h
 *
 * Created: 09.09.2015 16:21:04
 *  Author: sindrhan
 */ 


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

uint8_t ADC_read(uint8_t channel);
void ADC_init(void);



#endif /* ADC_DRIVER_H_ */