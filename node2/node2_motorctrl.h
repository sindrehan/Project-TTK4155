

#ifndef NODE2_MOTORCTRL_H_
#define NODE2_MOTORCTRL_H_

#include "arduino.h"
#include "Wire.h"

void motor_init();
void motor_position_init();
void motor_write(uint8_t speed, uint8_t dir);
int16_t motor_read();
uint8_t motor_reverse (uint8_t data);
void motor_reset_encoder ();
void motor_calibrate();



#endif /* NODE2_MOTORCTRL_H_ */