
#ifndef CAN_H_
#define CAN_H_

#include "mcp2515_driver.h"
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

#endif /* CAN_H_ */