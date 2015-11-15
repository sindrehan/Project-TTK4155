
#ifndef MCP2515_DRIVER_H_
#define MCP2515_DRIVER_H_

#include <avr/io.h>
#include "SPI_driver.h"

char MCP2515_read(char address);
void MCP2515_write(char data, char address);
void MCP2515_rts(char rts_port);
char MCP2515_read_status();
void MCP2515_bit_modify(char address, char mask, char data);
void MCP2515_reset();


#endif /* MCP2515_DRIVER_H_ */

