#include "SPI_driver.h"

void SPI_init(void){
	/* Set MOSI, SCK and SS output, all others input */
	DDRB = (1<<PB5)|(1<<PB7)|(1<<PB4);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_transmit(char cData){
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}

char SPI_receive(){
	SPI_transmit(0x00);
	return SPDR;
}

void SPI_enable(){
		PORTB &= ~(1<<PINB4);
}

void SPI_disable(){
	PORTB |= (1<<PINB4);
}