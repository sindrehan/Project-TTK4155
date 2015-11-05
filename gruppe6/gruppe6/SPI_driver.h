
#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include <avr/io.h>
#include <stdio.h>

void SPI_init(void);
void SPI_transmit(char cData);
char SPI_receive();
void SPI_enable();
void SPI_disable();


#endif /* SPI_driver_H_ */
