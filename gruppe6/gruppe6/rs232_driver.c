
#include "rs232_driver.h"


void UART_Init( uint16_t ubrr)
{
	//Set baud rate
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	
	//Enable receiver and transmitter
	UCSR0B = (1 << RXEN0 | (1<<TXEN0));
	
	//printf
	fdevopen((int (*)(char, struct __file*))&UART_Transmit, (int (*)(struct __file*))&UART_Receive);
}


void UART_Transmit( unsigned char data ){
	//Wait for empty transmit buffer
	while( !( UCSR0A & (1<<UDRE0)) );
	
	//	Put data into buffer, sends the data
	UDR0 = data;
}

unsigned char UART_Receive( void){
	//Wait for data to be received
	while( !(UCSR0A & (1<<RXC0)) );
	//Get and return received data from buffer
	return UDR0;
}

