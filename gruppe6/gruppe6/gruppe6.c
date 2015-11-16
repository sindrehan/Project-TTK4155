
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "rs232_driver.h"
#include "sram_test.h"
#include "adc_driver.h"
#include "joystick.h"
#include "test.h"
#include "oled_driver.h"
#include "definitions.h"




int main(void)
{	
	uint16_t ubrr = (F_CPU/16/BAUDRATE)-1;
	UART_Init(ubrr);
	can_init(MODE_NORMAL);
	JOY_init();
	OLED_init();
	menuitem* main_menu = menu_init();
	menuitem* current_menu = main_menu;
	
	JOY_position_t pos;
	
	uint8_t settings[] = {	MAINMENU,  // Game state
							SPEEDCTRL, // Control type
							MULTICARD  // Joystick type
	};
	
	uint8_t time[] = { 0,0,0 };	
		
	uint8_t prev_dir = NEUTRAL;
	
	uint8_t calibration_status = CAL_FINISHED;

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
		can_message_t msg_received = can_receive();
		switch (msg_received.id){
			case 0x02: //State update
				menu_change_gamestate(settings, msg_received.data[0]);
				break;
			case 0x03: //Game time update
				for (uint8_t i = 0; i < 3; i++){
					time[i] = msg_received.data[i];
				}
				break;

			case 0x04: //Calibration status
				calibration_status = msg_received.data[0];
				break;
		}
		
		switch (GAMESTATE){
			case MAINMENU:
				menu_print_mainmenu(current_menu);
				current_menu = menu_move(current_menu, &prev_dir, settings);
				break;
			case CALIBRATE:
				menu_print_calibrate(calibration_status);
				if (calibration_status == CAL_FINISHED){
					menu_change_gamestate(settings, PREGAME);
				}
				break;
			case PREGAME:
				menu_print_pregame();
				if (JOY_button(0)){ //Start
					menu_change_gamestate(settings, INGAME);
				}
				break;
			case INGAME:
				menu_print_ingame(time);
				if (JOY_button(1)){ //Reset
					menu_change_gamestate(settings, MAINMENU);
					current_menu = main_menu;
				}
				
				if (!JOY_button(2)){ //-> Brudd p� IR-str�le
					menu_change_gamestate(settings, POSTGAME);
				}
				if (JOYSTICKTYPE == MULTICARD){
					//pos = JOY_getPosition();
					//msg_commands.data[0] = pos.x;
					//msg_commands.data[1] = pos.y;
					//msg_commands.data[2] = JOY_button(0);
					//msg_commands.data[3] = JOY_button(1);
					//msg_commands.data[4] = JOY_button(2);
					//msg_commands.data[5] = ADC_read(2);
					//msg_commands.data[6] = ADC_read(3);
					//can_transmit(msg_commands);
				}
				break;
			case POSTGAME:
				menu_print_postgame(time);
				for (uint8_t i = 0; i<3; i++){
					time[i] = 0;
				}
				if (JOY_button(1)){
					menu_change_gamestate(settings, PREGAME);
				}
				if (Joy_getDirection() == LEFT){
					menu_change_gamestate(settings, MAINMENU);
					current_menu = main_menu;
				}
				break;
		}
	}
}



/* TODO
 - Flytt "menu_change_state()" til en egen fil for tilstandsmaskinfunksjoner
 - Sett opp arduino til � trigge tilstandsendringer
 - La calibrate funksjonen sende CAN-melding med calibration-status
N�dvending:
	 2.5 Lag en god og fin meny (P� OLED)
	 3 Flytt OLED til SRAM
	 4 Rydd opp minibreadboard
	 5 Typesetting ( char -> uint8 )
	 6 Navngiving
	 7 Definer konstanter p� en ryddig og oversiktlig m�te
	 8 Se om det er mulig � minimere antall globale variable

Eventuelt: 
	 1 Dokumentasjon (Kommentarer, UML?)
	 2 G� over breadboard, fiks farger osv.
	 4 Interrupt-based uart
	 6 Optional advanced: Create drawing functions like oled_line(x0,y0,x1,y1), oled_circle(x,y,r)
	 etc.
	 7 Send OLED over CAN
	 
Finn ut:
	 - How is it possible to write to the whole screen with the given memory mapping (512 bytes)
	 when the screen data is 1kB?
	 - Timere?

*/


	//
	//if (time[0] < 60){
	//if (time[1] < 60){
	//if (time[2] < 100){
	//time[2]++;
	//} else {
	//time[2] = 0;
	//time[1]++;
	//}
	//} else{
	//time[1] = 0;
	//time[0]++;
	//}
	//} else {
	//time[0] = 0;
	//time[1] = 0;
	//time[2] = 0;
	//}
	//_delay_ms(5);