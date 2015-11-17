// node2_mcp2515.h

#ifndef _NODE2_MCP2515_h
#define _NODE2_MCP2515_h

//#if defined(ARDUINO) && ARDUINO >= 100
	//#include "arduino.h"
//#else
	//#include "WProgram.h"
//#endif

#include "arduino.h"
#include "node2_spi.h"
#include "MCP2515.h"

uint8_t MCP2515_read(uint8_t address);
void MCP2515_write(uint8_t data, uint8_t address);
void MCP2515_rts(uint8_t rts_port);
char MCP2515_read_status(void);
void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data);
void MCP2515_reset(void);


#endif

