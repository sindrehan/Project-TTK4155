

#include "node2_ir.h"


uint16_t ir_read(){
	uint16_t sum = 0;
	for (uint8_t i = 0; i < 10; i++){
		sum += analogRead(A0);
	}
	return sum/10;
}

void gametime_counter(){
	game_time++;	
}

