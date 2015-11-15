
#include "node2_motorctrl.h"



void motor_init(){
	Wire.begin();
	DDRF	|= (1 << PF7)  //Encoder output enable
			|  (1 << PF6)  //Reset encoder
			|  (1 << PF5)  //Hi/Lo byte of encoder
			|  (1 << PF4)  //Motor enable
			|  (1 << PF3); //Motor direction
			
	DDRK = 0; //Set MJ2 to input
	
	PORTF	|= (1 << PF7)
			|  (1 << PF6)
			|  (1 << PF4);

}


void motor_write(uint8_t speed, uint8_t dir){
	if (dir){
		PORTF |= (1 << PF3);
	}
	else{
		PORTF &= ~(1 << PF3);
	}
	
	Wire.beginTransmission(0x28);	//DAC address
	Wire.write(0x00);				//Address DAC0
	Wire.write(speed);				//Output value
	Wire.endTransmission();
}

int16_t motor_read(){
	int16_t data = 0;
	PORTF &= ~(1 << PF7);
	PORTF &= ~(1 << PF5);
	_delay_us(20);
	data = PINK*0x100;
	PORTF |= (1 << PF5);
	_delay_us(20);
	data += PINK;
	PORTF &=  ~(1 << PF6);
	PORTF |=  (1 << PF6);
	PORTF |= (1 << PF7);
	return data;
}	

uint8_t motor_reverse (uint8_t data){
		data = ((data >> 1) & 0x55) | ((data << 1) & 0xaa);
		data = ((data >> 2) & 0x33) | ((data << 2) & 0xcc);
		data = ((data >> 4) & 0x0f) | ((data << 4) & 0xf0);
		return data;
}