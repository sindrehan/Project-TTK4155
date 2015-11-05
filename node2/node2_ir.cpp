

#include "node2_ir.h"


int ir_read(){
	int sum = 0;
	for (int i = 0; i < 10; i++){
		sum += analogRead(A0);
	}
	return sum/10;
}

void int_timer(){
	if (!game_over){
		game_time++;	
	}
}

