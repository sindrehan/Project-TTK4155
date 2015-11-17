

#ifndef NODE2_MOTORCTRL_H_
#define NODE2_MOTORCTRL_H_

#include "arduino.h"
#include "Wire.h"
#include <avr/io.h>
#include "../../../Desktop/Project-TTK4155/gruppe6/gruppe6/definitions.h"

void motor_init();
void motor_position_init();
void motor_write(uint8_t speed, uint8_t dir);
int16_t motor_read();
uint8_t motor_reverse (uint8_t data);
void motor_reset_encoder ();
void motor_calibrate(int16_t* pos);
void pi_controller(uint8_t joy_value, int16_t *position, int16_t *integration);



#endif /* NODE2_MOTORCTRL_H_ */
