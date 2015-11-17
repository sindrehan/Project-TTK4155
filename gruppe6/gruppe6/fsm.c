
#include "fsm.h"

void menu_change_gamestate(uint8_t *settings, uint8_t state){
	GAMESTATE = state;
	OLED_reset();
	can_message_t msg_settings = (can_message_t){
		.id = 0x02,
		.length = 3,
		.data = {	settings[0],    //Game state
			settings[1],	//Control type
			settings[2],	//Controller
		},
	};
	can_transmit(msg_settings);
}