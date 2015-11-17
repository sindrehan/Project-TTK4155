
#include <stdio.h>
#include <Arduino.h>
#include "TimerThree.h"
#include "Wire.h"
#include "Servo.h"

#include "../../../Desktop/Project-TTK4155/gruppe6/gruppe6/definitions.h"
#include "node2_can.h"
#include "node2_mcp2515.h"
#include "node2_spi.h"
#include "node2_test.h"
#include "node2_servo.h"
#include "node2_ir.h"
#include "node2_motorctrl.h"



uint32_t game_time = 0;

can_message_t time  = (can_message_t){
	.id = 0x03,
	.length = 3,
	.data = {	0, //Minutes
				0, //Seconds
				0, //Hundredths
	},
};

can_message_t cal_status  = (can_message_t){
	.id = 0x04,
	.length = 1,
	.data = { CAL_UNINITIATED,},
};

can_message_t msg_settings  = (can_message_t){
	.id = 0x02,
	.length = 3,
	.data = {	0,		//Game state
				0,		//Control method
				0,},	//Joystick type
};

static int uart_putchar (char c, FILE *stream){
	Serial.write(c);
	return 0;
}
static FILE uartout;

Servo servo;

//PI-controller variables
int16_t real_position = 0;
int16_t integration_error = 0;
int16_t ref_position = 0;



uint8_t settings[] = {	0,		//Game state
						0,		//Control method
						0 };	//Joystick type

int8_t joystick[] = {	0,0,	//x, y joystick
						0,0,	//Left-, Right button
						0,		//Joystick button
						0,0};	//Left-, Right slider

void setup()
{
	Serial.begin(9600);
	fdev_setup_stream(&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
	stdout = &uartout;
	
	Timer3.initialize(10000);
	
	can_init(MODE_NORMAL);
	servo.attach(3, 900, 2100);
	
	motor_init();
	pinMode(4, OUTPUT);
}

void loop()
{	
	
	can_message_t msg = can_receive();
	switch (msg.id){
		case 0x01:
			for (uint8_t i = 0; i < msg.length; i++){
				joystick[i] = msg.data[i];
			}
		break;
		case 0x02:
			for (uint8_t i = 0; i < msg.length; i++){
				if (settings[i] != msg.data[i]){
					settings[i] = msg.data[i];
				}
			}
		break;
	}
	
	if (JOYSTICKTYPE == DUALSHOCK3){
		//Place dualshock values in joystick array
	}
	switch (GAMESTATE) {
		case MAINMENU:
			//Everything is handled at node 1
			break;
		case CALIBRATE:
			cal_status.data[0] = CAL_INITIATED;
			can_transmit(cal_status);
			motor_calibrate(&real_position);
			cal_status.data[0] = CAL_FINISHED;
			can_transmit(cal_status);
			GAMESTATE = PREGAME;
		case PREGAME:
			//Everything is handled at node 1
			break;
		case INGAME:
			Timer3.attachInterrupt(gametime_counter);
			//Convert from  X = (-100) % - 100 % to 0 - 180 degrees
			servo.write((uint8_t) (( ((float)(-1)*joystick[0]) / 100)*90)+90);
			switch (CTRLTYPE) {
				case SPEEDCTRL:
					if (joystick[1] > 0){
						motor_write(joystick[1]*128/100, 1);
					}
					else{
						motor_write(-1*joystick[1]*128/100, 0);
					}
					break;
				case POSCTRL:
					ref_position = (uint8_t) -joystick[6];
					ref_position *= 9000/255;
					real_position += motor_read();
					integration_error += ref_position - real_position;
					int16_t gain = (((ref_position - real_position)*K_P) + integration_error*K_I);
					if (gain > 0){
						motor_write(gain, 0);
					}
					else{
						motor_write(-gain, 1);
					}
					break;
			}
			if (!joystick[4]){
				digitalWrite(SOLENOIDPIN, LOW);
				} else {
				digitalWrite(SOLENOIDPIN, HIGH);
			}
			if (ir_read() < IRLIMIT){
				Timer3.detachInterrupt();			
				GAMESTATE = POSTGAME;
				for (uint8_t i = 0; i < msg_settings.length; i++){
					msg_settings.data[i] = settings[i];
				}
				can_transmit(msg_settings);
				
			} 
			else {
				//Update time
				time.data[0] = game_time/6000;			//Minutes
				time.data[1] = (game_time/100) % 60;	//Seconds
				time.data[2] = game_time % 100;			//Hundredths
				can_transmit(time);
			}
			break;
		case POSTGAME:
			motor_write(0,0);
			game_time = 0;
			break;
	}
}
