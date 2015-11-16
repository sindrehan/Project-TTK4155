
#define DEFINITIONS "../../../Desktop/Project-TTK4155/gruppe6/gruppe6/definitions.h"

#include <stdio.h>
#include <Arduino.h>
#include "TimerThree.h"
#include "Wire.h"
#include "Servo.h"

#include "node2_can.h"
#include "node2_mcp2515.h"
#include "node2_spi.h"
#include "node2_test.h"
#include "node2_servo.h"
#include "node2_ir.h"
#include "node2_motorctrl.h"
#include DEFINITIONS

uint32_t game_time = 0;

can_message_t time  = (can_message_t){
.id = 0x03,
.length = 3,
.data = {	0, //Minutes	
			0, //Seconds	
			0, //Hundredths 
		},
};

static int uart_putchar (char c, FILE *stream){
    Serial.write(c);
    return 0;
}
static FILE uartout;

Servo servo;
uint8_t informed = 0;
int16_t position = 0;
int16_t desired_position = 0;
uint8_t mode = 0;
int16_t integration_error = 0;

uint8_t state = MAINMENU;

uint8_t settings[] = { 0,0,0 };
int8_t joystick[] = { 0,0,0,0,0,0,0};

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
	
	motor_calibrate(&position);
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
				settings[i] = msg.data[i];
			}
			break;
	}
	
	if (settings[2]){
		//Place dualshock values in joystick array
	}
	switch (state) {
		case MAINMENU:
			
			if(settings[0]){
				state = CALIBRATE;
			}
			break;
		case CALIBRATE:
			//OLED msg: calibrating initiated
			//motor_calibrate(&position);
			//OLED msg: calibrating completed
			state = PREGAME;
		case PREGAME:
			printf("joystick %d\n", joystick[4]); //Fungerer med printf
			if(!settings[2]){
				//Oled msg: press to start
				//PS3 control
			} else{
				if (!joystick[4]){
					//OLED msg: pres to start
					state = INGAME;
				}
			}
			break;
		case INGAME:
			Timer3.attachInterrupt(gametime_counter);
			//Convert from  X = � 100 % to 0 - 180 degrees
			servo.write((int) (( ((float)(-1)*joystick[0]) / 100)*90)+90);
			switch (settings[1]) {
				case SPEEDCTRL:
					if (joystick[1] > 0){
						motor_write(joystick[1]*128/100, 1);
					}
					else{
						motor_write(-1*joystick[1]*128/100, 0);
					}
					break;
				case POSCTRL:
					desired_position = (uint8_t) -joystick[6];
					desired_position *= 9000/255;
					position += motor_read();
					integration_error += (desired_position - position);
			
					if (((desired_position - position)/40 + integration_error/6000) > 0){
						motor_write((desired_position - position)/40 + integration_error/6000, 0);
					}
					else{
						motor_write( ( position - desired_position)/40 + integration_error/6000, 1);
					}
					break;
			}
			if (!joystick[4]){
				digitalWrite(SOLENOIDPIN, LOW);
				} else {
				digitalWrite(SOLENOIDPIN, HIGH);
			}
			if (ir_read() < IRLIMIT){
				//Timer3.detachInterrupt();
				
				state = POSTGAME;
			} else {
				time.data[0] = game_time/6000;
				time.data[1] = (game_time/100) % 60;
				time.data[2] = game_time % 100;
				can_transmit(time);
			}
			break;
		case POSTGAME:
			//OLED msg: Game ended. 
			break;
	}
	//can_printmsg(msg);
}


		
	
	//if (game_over){
		////Use the informed variable to avoid printing multiple times
		//if (ir_read() < IRLIMIT && !informed){
			//printf("Remove ball before resetting!\n");
			//informed = 1;
		//}
		//else if(ir_read() > IRLIMIT && informed){
			//printf("Resetting: %d\n", msg.data[3]);
			//game_over = 0;
			//informed = 0;
		//}
		//else if(ir_read() > IRLIMIT){
			//printf("Resetting: %d\n", msg.data[3]);
			//game_over = 0;
		//}
	//}
//
	//if (!(game_over) && (ir_read() < IRLIMIT)){
		//game_over = 1;
		//printf("Game time: %d.%d%ds\n", game_time/100, game_time%10, game_time%1 );
		//game_time = 0;
	//} else {
//
	//}
	//can_transmit(time);
	

	//printf("Positon: %d\n", position);
	
	//printf("Encoder: %d\n", motor_read());
	//printf("IR: %d\n", ir_read());



