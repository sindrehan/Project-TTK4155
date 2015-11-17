
#ifndef MCP2515_DRIVER_H_
#define MCP2515_DRIVER_H_

#include <avr/io.h>
#include "SPI_driver.h"

uint8_t MCP2515_read(uint8_t address);
void MCP2515_write(uint8_t data, uint8_t address);
void MCP2515_rts(uint8_t rts_port);
uint8_t MCP2515_read_status(void);
void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
void MCP2515_reset(void);


#endif /* MCP2515_DRIVER_H_ */

