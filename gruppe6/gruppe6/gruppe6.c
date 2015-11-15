
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
	
	char* main_menu[] = {3, "Main Menu", "New game", "Options", "Back"};
	char* new_game[] = {3, "New Game", "Single player", "Double player", "Back"};
	char* single_player[] = {1, "I", "Single player", "Double player", "Back"};
	int ubrr = (F_CPU/16/9600)-1;
	UART_Init(ubrr);
	
	//can_init(MODE_NORMAL);
	//JOY_init();
	//OLED_init();	
	test_oled_menu();
	//can_message_t commands = (can_message_t){
		//.id = 0x01,
		//.length = 5,
		//.data = {0, 0,	//Joystick positions
				 //0, 0,	//Left and right button
				 //0,		//Joystick button
				//},
	//};
	//
	//JOY_position_t pos;
	//
	//while(1){
		//pos = JOY_getPosition();
		//commands.data[0] = pos.x;
		//commands.data[1] = pos.y;
		//commands.data[2] = JOY_button(0);
		//commands.data[3] = JOY_button(1);
		//commands.data[4] = JOY_button(2);
		//printf("JOy button: %d\n",commands.data[4]);
		//can_transmit(commands);
	//}
	
	
	
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