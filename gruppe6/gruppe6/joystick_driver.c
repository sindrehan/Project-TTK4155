/*
* joystick_driver.c
*
* Created: 10.09.2015 19:08:52
*  Author: sindrhan
*/

#include "joystick.h"
#include "adc_driver.h"
uint8_t JOY_x_init_pos, JOY_y_init_pos;

void JOY_init(){
	ADC_init();
	
	DDRB &= ~(1<<PINB0) & ~(1<<PINB1) & ~(1<<PINB2);
	PORTB |= (1<<PINB0) | (1<<PINB1) | (1<<PINB2);
	
	JOY_calibrate();
}

void JOY_calibrate(){
	JOY_x_init_pos = ADC_read(0);
	JOY_y_init_pos = ADC_read(1);
}

bool JOY_button(int button){ //0: LEFT, 1: RIGHT, 2: Joystick
	switch(button){
		case 0:
			return !(!(PINB & (1<<PINB0)));
		case 1:
			return !(!(PINB & (1<<PINB1)));
		case 2:
			return !(!(PINB & (1<<PINB2)));
		default:
			return false;
	}
}

JOY_position_t JOY_getPosition(){
	int x_pos = (ADC_read(0)-JOY_x_init_pos)*100/127;
	int y_pos = (ADC_read(1)-JOY_y_init_pos)*100/127;
	JOY_position_t result;
	result.x = x_pos;
	result.y = y_pos;
	return result;
}

JOY_direction_t Joy_getDirection(){
	JOY_position_t position = JOY_getPosition();
	JOY_direction_t direction;
	int limit = 45;
	if(position.x < -limit){
		direction = LEFT;
	}
	else if(position.x > limit){
		direction = RIGHT;
	}
	else if(position.y > limit){
		direction = UP;
	}
	else if (position.y < -limit){
		direction = DOWN;
	}
	else{
		direction = NEUTRAL;
	}
	return direction;
}