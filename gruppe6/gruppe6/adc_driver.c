

#include "adc_driver.h"

void ADC_init(void){
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	DDRB &= ~(1<<PINB3);
}

uint8_t ADC_read(uint8_t channel){
	volatile uint8_t *adc = (uint8_t *) 0x1400;
	
	*adc = 4+channel;
	
	_delay_us(10);								//Give adc some time to remove the previous interrupt
	
	while( (PINB & (1<<PINB3) ) ){}
	return *adc; 
}

