
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
#include "fsm.h"




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
	
	uint8_t time[] = {	0,		//Minutes
						0,		//Seconds
						0 };	//Hundredths
		
	uint8_t prev_dir = NEUTRAL;
	
	uint8_t calibration_status = CAL_UNINITIATED;

	can_message_t msg_joystick = (can_message_t){
		.id = 0x01,
		.length = 7,
		.data = {0,0,	//x, y Joystick
				 0,0,	//Left-, Right button
				 0,		//Joystick button
				 0,0,	//Left-, Right slider
				 },
	};
	

	
	while(1){
		can_message_t msg_received = can_receive();
		switch (msg_received.id){
			//case 0x01:
				//for 
			case 0x02: //State update
				fsm_change_state(settings, msg_received.data[0]);
				printf("Msg received: %d\n", msg_received.data[0]);
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
					fsm_change_state(settings, PREGAME);
				}
				break;
			case PREGAME:
				menu_print_pregame();
				if (!JOY_button(2)){ //Start
					fsm_change_state(settings, INGAME);
				}
				break;
			case INGAME:
				menu_print_ingame(time);
				if (JOYSTICKTYPE == MULTICARD){
					pos = JOY_getPosition();
					msg_joystick.data[0] = pos.x;
					msg_joystick.data[1] = pos.y;
					msg_joystick.data[2] = JOY_button(0);
					msg_joystick.data[3] = JOY_button(1);
					msg_joystick.data[4] = JOY_button(2);
					msg_joystick.data[5] = ADC_read(2);
					msg_joystick.data[6] = ADC_read(3);
					can_transmit(msg_joystick);
				}
				break;
			case POSTGAME:
				menu_print_postgame(time);
				if (JOY_button(0)){
					fsm_change_state(settings, PREGAME);
				}
				if (Joy_getDirection() == LEFT){
					fsm_change_state(settings, MAINMENU);
					current_menu = main_menu;
				}
				if (GAMESTATE != POSTGAME){
					for (uint8_t i = 0; i<3; i++){
						time[i] = 0;
					}
				}
				break;
		}
	}
}



/* TODO
 - Flytt "menu_change_state()" til en egen fil for tilstandsmaskinfunksjoner

Nødvending:
	 4 Rydd opp minibreadboard
	 check 5 Typesetting ( char -> uint8 )
	 check 6 Navngiving
	 7 Definer konstanter på en ryddig og oversiktlig måte
	 check 8 Se om det er mulig å minimere antall globale variable

Eventuelt: 
	 1 Dokumentasjon (Kommentarer, UML?)
	 2 Gå over breadboard, fiks farger osv.
	 4 Interrupt-based uart
	 6 Optional advanced: Create drawing functions like oled_line(x0,y0,x1,y1), oled_circle(x,y,r)
	 etc.
	 7 Send OLED over CAN
	 
Finn ut:
	 - How is it possible to write to the whole screen with the given memory mapping (512 bytes)
	 when the screen data is 1kB?
	 - Timere?

*/