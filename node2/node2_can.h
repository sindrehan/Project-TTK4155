// node2_can.h

#ifndef _NODE2_CAN_h
#define _NODE2_CAN_h


#include "arduino.h"
#include "node2_mcp2515.h"
#include "MCP2515.h"

typedef struct{
	uint8_t id;
	uint8_t length;
	int8_t data[8];
} can_message_t;

void can_init(uint8_t mode);
void can_transmit(can_message_t msg);

can_message_t can_receive(void);
void can_printmsg(can_message_t m);
#endif

