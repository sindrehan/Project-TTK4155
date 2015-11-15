
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "rs232_driver.h"
#include "sram_test.h"
#include "adc_driver.h"
#include "joystick.h"
#include "test.h"
#include "oled_driver.h"
#include "definations.h"



int main(void)
{	
	int ubrr = (F_CPU/16/9600)-1;
	UART_Init(ubrr);
	
	can_init(MODE_NORMAL);
	JOY_init();
	OLED_init();
	menuitem* current_menu = menu_init();
	
	JOY_position_t pos;
	
	uint8_t settings[] = {	MAINMENU,  // Game mode
						SPEEDCTRL, // Control type
						MULTICARD  // Joystick type
	};
	
	uint8_t time[] = { 0,0,0 };	
		
	uint8_t prev_dir = NEUTRAL;
	
	can_message_t msg_received;

	can_message_t msg_commands = (can_message_t){
		.id = 0x01,
		.length = 7,
		.data = {0,0,	//x, y joystick
				 0,0,	//Left-, Right button
				 0,		//Joystick button
				 0,0,	//Left-, Right slider
				 },
	};
	

	
	while(1){
		msg_received = can_receive();
		if (msg_received.id == 0x03){
			time[0] = msg_received.data[0];
			time[1] = msg_received.data[1];
			time[2] = msg_received.data[2];
		}
		
		
		switch (settings[0]){
			case MAINMENU:
				menu_print(current_menu);
				current_menu = menu_move(current_menu, &prev_dir, settings);
				//printf("Setup: %d %d %d \n", settings[0], settings[1], settings[2]);
				break;
			case SINGLEPLAYERMENU:
				print_singleplayer();
				
				break;
			case DOUBLEPLAYERMENU:
				//Stuff to print
				break;
		}
		
		if (settings[0] == SINGLEPLAYERMENU || settings[0] == DOUBLEPLAYERMENU){
			switch (settings[2]) {
				case DUALSHOCK3:
				break;
				case MULTICARD:
				pos = JOY_getPosition();
				msg_commands.data[0] = pos.x;
				msg_commands.data[1] = pos.y;
				msg_commands.data[2] = JOY_button(0);
				msg_commands.data[3] = JOY_button(1);
				msg_commands.data[4] = JOY_button(2);
				msg_commands.data[5] = ADC_read(2);
				msg_commands.data[6] = ADC_read(3);
				can_transmit(msg_commands);				
				break;
			}
		}
		//switch 
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