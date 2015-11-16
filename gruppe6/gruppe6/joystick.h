/*
 * joystick.h
 *
 * Created: 10.09.2015 19:09:12
 *  Author: sindrhan
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <avr/io.h>

typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL
} JOY_direction_t;
	
typedef struct {
	int8_t x;
	int8_t y;
} JOY_position_t;
	

void JOY_init();
void JOY_calibrate();
uint8_t JOY_button(uint8_t button);
JOY_position_t JOY_getPosition();
JOY_direction_t Joy_getDirection();



#endif /* JOYSTICK_H_ */