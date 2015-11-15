
#include "node2_spi.h"

void SPI_init(void){
	/* Set MOSI, SCK and SS output, all others input */
	DDRB |= (1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	DDRB &= ~(1<<DDB3);
	/* Enable SPI, Master, set clock rate fck/64 */
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR1);
}

void SPI_transmit(uint8_t cData){
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}

uint8_t SPI_receive(){
	SPI_transmit(0x00);
	return SPDR;
}

void SPI_enable(){
	PORTB &= ~(1<<PB0);
}

void SPI_disable(){
	PORTB |= (1<<PB0);
}