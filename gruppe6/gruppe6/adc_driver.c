/*
 * adc_driver.c
 *
 * Created: 09.09.2015 16:20:45
 *  Author: sindrhan
 */ 



#include "adc_driver.h"

void ADC_init(void){
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	DDRB &= ~(1<<PINB3);
}

uint8_t ADC_read(uint8_t channel){
	volatile char *adc = (char *) 0x1400;
	
	*adc = 4+channel;
	
	_delay_us(10); //Give adc some time to remove the previous interrupt
	
	while( (PINB & (1<<PINB3) ) ){}
	return *adc; 
}

