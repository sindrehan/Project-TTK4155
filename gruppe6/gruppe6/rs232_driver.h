#pragma once

#include <avr/io.h>
#include <stdio.h>

void UART_Init( uint16_t ubrr);
void UART_Transmit( unsigned char data );
unsigned char UART_Receive( void);


