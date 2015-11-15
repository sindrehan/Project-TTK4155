
#include "node2_servo.h"


void node2_servo_init(uint8_t pin, Servo minservo){
	minservo.attach(pin, 900, 2100);
}
