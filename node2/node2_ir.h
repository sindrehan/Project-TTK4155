/*
 * node2_ir.h
 *
 * Created: 21.10.2015 12:58:39
 *  Author: sindrhan
 */ 


#ifndef NODE2_IR_H_
#define NODE2_IR_H_

#include "Arduino.h"

extern volatile int game_over;
extern long game_time;

int ir_read();
void int_timer();

#endif /* NODE2_IR_H_ */
