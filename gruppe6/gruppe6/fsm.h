
#ifndef FSM_H_
#define FSM_H_

#include "oled_driver.h"
#include "can.h"
#include "definitions.h"

void fsm_change_state(uint8_t *settings, uint8_t state);


#endif /* FSM_H_ */