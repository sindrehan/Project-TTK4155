
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

volatile int game_over = 1;
long game_time = 0;

can_message_t new_score  = (can_message_t){
.id = 0x03,
.length = 1,
.data = {0,},
};

static int uart_putchar (char c, FILE *stream){
    Serial.write(c);
    return 0;
}
static FILE uartout;

Servo servo;
int informed = 0;
uint8_t speed = 0;

void setup()
{
	Serial.begin(9600);
	fdev_setup_stream(&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &uartout;
	
	Timer3.initialize(1000000);
	Timer3.attachInterrupt(int_timer, 10000);
	
	can_init(MODE_NORMAL);
	servo.attach(3, 900, 2100);
	
	motor_init();

	pinMode(4, OUTPUT);
}

void loop()
{
	can_message_t msg = can_receive();
	//can_printmsg(msg);
	//Convert from  X = ± 100 % to 0 - 180 degrees
	servo.write((int) (( ((float)(-1)*msg.data[0]) / 100)*90)+90);	
	if (msg.data[1] > 0){
		motor_write(msg.data[1]*128/100, 1);				
	}
	else{
		motor_write(-1*msg.data[1]*128/100, 0);	
	}
	
	if (game_over){
		//Use the informed variable to avoid printing multiple times
		if (ir_read() < 50 && !informed){
			printf("Remove ball before resetting!\n");
			informed = 1;
		}
		else if(ir_read() > 50 && informed){
			printf("Resetting: %d\n", msg.data[3]);
			game_over = 0;
			informed = 0;
		}
		else if(ir_read() > 50){
			printf("Resetting: %d\n", msg.data[3]);
			game_over = 0;
		}
	}
	if (!msg.data[4]){
		//printf("Button pressed\n");
		digitalWrite(4, LOW);

	} else {
		digitalWrite(4, HIGH);
		//printf("button released\n");
	}	
	
	if (!(game_over) && (ir_read() < 50)){
		game_over = 1;
		new_score.data[0] = game_time;
		printf("Game time: %d.%d%ds\n", game_time/100, game_time%10, game_time%1 );
		game_time = 0;
	}
	
	printf("Encoder: %d\n", motor_read());

}


