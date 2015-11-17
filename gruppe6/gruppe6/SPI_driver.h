
#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include <avr/io.h>
#include <stdio.h>

void SPI_init(void);
void SPI_transmit(uint8_t cData);
uint8_t SPI_receive(void);
void SPI_enable(void);
void SPI_disable(void);


#endif /* SPI_driver_H_ */
