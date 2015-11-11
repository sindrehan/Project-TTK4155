
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "rs232_driver.h"
#include "sram_test.h"
#include "adc_driver.h"
#include "joystick.h"
#include "test.h"
#include "oled_driver.h"

/*
Menu features:
	submenus
	move back to correct parent menu
	void->void fn ptr
	
Menu structure:
	tree-like
		array of submenus
		ptr to parent
		next = parents' submenus' next
		
		
struct menuitem {
	char* name;
	struct {
		uint8_t		number;
		menuitem**	entries;
	} submenus;
	menuitem*	parent;
	void (fn*)(void);
}


uint8_t menu_submenuIndex(menuitem* m){
	if(m->parent){
		for(uint8_t idx = 0; idx < m->parent->submenus.number; idx++){
			if(sub == m->parent->submenus.entries[idx]){
				return idx;
			}
		}
	}
	return 0;
}

menuitem* menu_right(menuitem* m, uint8_t idx){
	if(idx <= m->submenus.number  &&  m->submenus.entries != NULL){
		return m->submenus.entries[idx];
	} else {
		return m;
	}
}

menuitem* menu_left(menuitem* m){
	if(m->parent){
		return m->parent;
	} else {
		return m;
	}
}

menuitem* menu_up(menuitem* m){
	uint8_t thisIdx = menu_submenuIndex(m);
	if(thisIdx > 0){
		return m->parent->submenus.entries[thisIdx-1];
	} else {
		return m;
	}
}

menuitem* menu_down(menuitem* m){
	uint8_t thisIdx = menu_submenuIndex(m);
	if(thisIdx < m->parent->submenus.number){
		return m->parent->submenus.entries[thisIdx+1];
	} else {
		return m;
	}	
}

menuitem* menu_new(char* name, uint8_t numSubmenus, void fn(void)){
	menuitem* m = malloc(sizeof(menuitem));
	memset(m, 0, sizeof(menuteim));
	
	m->submenus.entries = malloc(sizeof(menuitem*) * numSubmenus);
	m->fn = fn;
	m->name = name;
	
	return m;
}
	

menuitem* menu_init(){

	menuitem* main_menu = menu_new("Main menu", 3, NULL);
	main_menu->submenus.entries[0] = menu_new("Submenu 0", 0, NULL);
	main_menu->submenus.entries[1] = menu_new("Submenu 1", 0, NULL);
	main_menu->submenus.entries[2] = menu_new("Submenu 2", 0, NULL);


	void menu_assign_parents(menuitem* base){
		for(uint8_t idx = 0; idx < m->submenus.number; idx++){
			m->submenus.entries[idx]->parent = base;
			if(m->submenus.number > 0){
				menu_assign_parents(m->submenus.entries[idx]);
			}
		}
	}
	menu_assign_parents(main_menu);
	return main_menu;
}

	
	
*/


int main(void)
{	
	char* main_menu[] = {"Main Menu:", "New game", "Options", NULL};
	char* new_game[] = {3, "New Game:", "Single player", "Double player", "Back"};
	char* single_player[] = {2, "Single player:", "Ready?", "Back"};
	char* double_player[] = {2, "Double player:", "Ready?", "Back"};
	char* options[] = {3, "Options:","Control type" "Controller" "back"};
	char* controller[] = {2, "Choose controller:", "IO-board", "DualShock 3"};
	char* control_type[] = {3,"Control type:", "Speed", "Position"};
	
	
	uint8_t mode = 0; // 0: Setupmode; 1: 
	
	

	int ubrr = (F_CPU/16/9600)-1;
	UART_Init(ubrr);
	
	can_init(MODE_NORMAL);
	JOY_init();
	OLED_init();
	//test_oled_menu();
	can_message_t commands = (can_message_t){
		.id = 0x01,
		.length = 7,
		.data = {0,0,	//x,y
				 0,0,	//Left/Right button
				 0,		//Joybutton
				 0,0,	//Left/Right slider
				 },
	};
	
	can_message_t setup = (can_message_t){
		.id = 0x02,
		.length = 4,
		.data = {0, //Players
				 0,	//Control type
				 0,	//Controller
				 },
	};
	
	JOY_position_t pos;
	
	while(1){
		switch(mode){
			case 0:
				switch(menu_move_selector(main_menu)){
					case 0:
						switch(menu_move_selector(new_game)){
							case 0:
								switch(menu_move_selector(single_player)){
									case 0:
										//Skift modus
								
										setup.data[0] = 0;
										break;
									case 1:
										break;
								}
								break;
							case 1:
								switch(menu_move_selector(double_player)){
									case 0:
										//Skift modus
										setup.data[0] = 1;
										break;
									case 1:
										break;
								}
								break;
						}
					case 1:
						switch(menu_move_selector(options)){
							case 0:
								switch(menu_move_selector(control_type)){
									case 0:
										//Speed
										setup.data[1] = 0;
										break;
									case 1:
										//Position
										setup.data[1] = 1;
										break;
								}
								break;
							case 1:
								switch(menu_move_selector(controller)){
									case 0:
										//IO-board
										setup.data[2] = 0;
									case 1:
										//Dualshock3
										setup.data[2] = 1;
								}
								break;
							case 2:
								//back
								break;
						}
						break;
				break;
			}
			case 1:
			//pos = JOY_getPosition();
			//commands.data[0] = pos.x;
			//commands.data[1] = pos.y;
			//commands.data[2] = JOY_button(0);
			//commands.data[3] = JOY_button(1);
			//commands.data[4] = JOY_button(2);
			//commands.data[5] = ADC_read(2);
			//commands.data[6] = ADC_read(3);
			////printf("JOy button: %d\n",commands.data[4]);
			//can_transmit(commands);
			break;
		}
		
		
		//pos = JOY_getPosition();
		//commands.data[0] = pos.x;
		//commands.data[1] = pos.y;
		//commands.data[2] = JOY_button(0);
		//commands.data[3] = JOY_button(1);
		//commands.data[4] = JOY_button(2);
		//commands.data[5] = ADC_read(2);
		//commands.data[6] = ADC_read(3);
		////printf("JOy button: %d\n",commands.data[4]);
		//can_transmit(commands);
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