


#include "test.h"

void test_adc(){
	ADC_init();
	while (1)
	{
		printf("X: %u\n", ADC_read(0)); //0
		printf("Y: %u\n", ADC_read(1)); //1
		
		printf("Left Slider: %u\n", ADC_read(2)); // 2
		printf("Right Slider: %u\n", ADC_read(3)); //3
		
		uint8_t left_button = 0;
		uint8_t right_button = 0;
		
		if((PINB & (1<<PINB0))){
			left_button = 1;
		}
		
		if((PINB & (1<<PINB1))){
			right_button = 1;
		}
		
		printf("Left button: %u\n", left_button);
		printf("Right button: %u\n\n", right_button);
		_delay_ms(100);
	}
}

void test_joystick(){
	JOY_init();
	while(1){
		JOY_position_t XY  = JOY_getPosition();
		
		printf("\nX: %d %%\n", XY.x);
		printf("Y: %d %%\n", XY.y);
		
		switch(Joy_getDirection()){
			case UP:
			printf("Direction: UP");
			break;
			case DOWN:
			printf("Direction: DOWN");
			break;
			case LEFT:
			printf("Direction: LEFT");
			break;
			case RIGHT:
			printf("Direction: RIGHT");
			break;
			case NEUTRAL:
			printf("Direction: NEUTRAL");
			break;
		}
		
		printf("\nLeft button: %s \n", JOY_button(0) ? "On" : "Off");
		printf("Right button: %s \n\n", JOY_button(1) ? "On" : "Off");
		printf("Joystick button: %s \n\n", JOY_button(2) ? "On" : "Off");
		
		_delay_ms(100);
	}
}

void test_oled_menu(){
	JOY_init();
	OLED_init();
	char* main_menu[] = {"Submenu1", "Submenu2", "Submenu3"};
	char* sub1[] = {"Back to main", "Option 1", "Option 2", "Option 3"};
	char* sub2[] = {"Back to main", "Option 1", "Option 2", "Option 3"};
	char* sub3[] = {"Back to main", "Option 1", "Option 2", "Option 3"};
	
	while(1){
		switch(menu_move_selector(main_menu, 3)){
			case 0:
			printf("Sub1, option %d\n", menu_move_selector(sub1, 3));
			break;
			case 1:
			printf("Sub2, option %d\n", menu_move_selector(sub2, 3));
			break;
			case 2:
			printf("Sub3, option %d\n", menu_move_selector(sub3, 3));
			break;
		}
	}
}

void test_mcp(){
	SPI_init();
	for (char i = 'a'; i<='z'; i++){
		printf("Memory 0x36: %c\n", MCP2515_read(0x36));
		printf("Writing '%c' to 0x36\n",i);
		MCP2515_write(i,0x36);
		printf("Memory 0x36: %c\n\n", MCP2515_read(0x36));
	}
}

void test_can(){
	can_init(MODE_LOOPBACK);
	can_message_t testmelding  = (can_message_t){
		.id = 0xff,
		.length = 4,
		.data = {1, 2, 3, 4,},
	};
	//can_message_t testmelding2  = (can_message_t){
		//.id = 0x69,
		//.length = 4,
		//.data = {4, 5, 6, 7,},
	//};
	can_transmit(testmelding);
	
	can_message_t mottatt_melding = can_receive();

	printf("id: %3d  ", mottatt_melding.id);
	printf("len: %3d  ", mottatt_melding.length);
	printf("Melding: [ %d %d %d %d ]\n",	mottatt_melding.data[0],
											mottatt_melding.data[1],
											mottatt_melding.data[2], 
											mottatt_melding.data[3]);
	//can_transmit(testmelding2);
	//mottatt_melding = can_receive();
//
	//printf("id: %3d  ", mottatt_melding.id);
	//printf("len: %3d  ", mottatt_melding.length);
	//printf("Melding: [ %d %d %d %d ]\n",	mottatt_melding.data[0],
	//mottatt_melding.data[1],
	//mottatt_melding.data[2],
	//mottatt_melding.data[3]);
		
}