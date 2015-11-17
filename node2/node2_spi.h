
#ifndef _NODE2_SPI_h
#define _NODE2_SPI_h

#include "arduino.h"

void SPI_init(void);
void SPI_transmit(uint8_t cData);
uint8_t SPI_receive(void);
void SPI_enable(void);
void SPI_disable(void);

#endif

