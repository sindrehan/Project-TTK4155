
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "rs232_driver.h"
#include "sram_test.h"
#include "adc_driver.h"
#include "joystick.h"
#include "test.h"
#include "oled_driver.h"



int main(void)
{	
	int ubrr = (F_CPU/16/9600)-1;
	UART_Init(ubrr);
	
	can_init(MODE_NORMAL);
	JOY_init();
	OLED_init();
	menuitem* current_menu = menu_init();
	uint8_t prev_dir = NEUTRAL;
	//current_menu = current_menu->submenus.entries[0];

	//can_message_t commands = (can_message_t){
		//.id = 0x01,
		//.length = 7,
		//.data = {0,0,	//x,y
				 //0,0,	//Left/Right button
				 //0,		//Joybutton
				 //0,0,	//Left/Right slider
				 //},
	//};
	//
	can_message_t setup = (can_message_t){
		.id = 0x02,
		.length = 4,
		.data = {0, //Players
			0,	//Control type
			0,	//Controller
		},
	};
	//
	//JOY_position_t pos;
	
	while(1){	
		
		//pos = JOY_getPosition();
		//commands.data[0] = pos.x;
		//commands.data[1] = pos.y;
		//commands.data[2] = JOY_button(0);
		//commands.data[3] = JOY_button(1);
		//commands.data[4] = JOY_button(2);
		//commands.data[5] = ADC_read(2);
		//commands.data[6] = ADC_read(3);
		//can_transmit(commands);

		menu_print(current_menu);
		//printf("HEI\n");
		current_menu = menu_move(current_menu, &prev_dir, &setup);
	}
	
	
	
}



//Ch1 - AXIS1
//Ch2 - AXIS2
//Ch3 - BUTTON
//
//Left slider - PortB6
//Right slider -  PortD2


/* TODO
Nødvending:
	 1 Skriv om til å bare sende én can-melding fra node 1.
	 2 Posisjonskontroller
	 2.5 Lag en god og fin meny (På OLED)
	 3 Flytt OLED til SRAM
	 4 Rydd opp minibreadboard
	 5 Typesetting ( char -> uint8 )
	 6 Navngiving
	 7 Definer konstanter på en ryddig og oversiktlig måte
	 8 Se om det er mulig å minimere antall globale variable

Eventuelt: 
	 1 Dokumentasjon (Kommentarer, UML?)
	 2 Gå over breadboard, fiks farger osv.
	 3 Fiks DSUB9
	 4 Interrupt-based uart
	 5 OLED printf
	 6 Optional advanced: Create drawing functions like oled_line(x0,y0,x1,y1), oled_circle(x,y,r)
	 etc.
	 7 Send OLED over CAN
	 
Finn ut:
	 - How is it possible to write to the whole screen with the given memory mapping (512 bytes)
	 when the screen data is 1kB?
	 - Timere?

*/