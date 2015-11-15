/*
 * node2_ir.h
 *
 * Created: 21.10.2015 12:58:39
 *  Author: sindrhan
 */ 


#ifndef NODE2_IR_H_
#define NODE2_IR_H_

#include "Arduino.h"

extern uint32_t game_time;

uint16_t ir_read();
void gametime_counter();

#endif /* NODE2_IR_H_ */
