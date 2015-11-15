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
void MCP2515_write(char data, char address);
void MCP2515_rts(char rts_port);
char MCP2515_read_status();
void MCP2515_bit_modify(char address, char mask, char data);
void MCP2515_reset();


#endif

