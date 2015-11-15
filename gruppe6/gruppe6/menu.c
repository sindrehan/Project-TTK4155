
#include "menu.h"

uint8_t menu_arrow_index(menuitem* m){
	for(uint8_t i = 0; i < m->submenus.number; i++){
		if(m->submenus.entries[i]->arrow_flag){
			return i;
		}
	}
	return 0;
}

menuitem* menu_right(menuitem* m, uint8_t *setup){
	uint8_t arrow_index = menu_arrow_index(m);
	if(m->submenus.entries[arrow_index]->submenus.number != 0){
		return m->submenus.entries[arrow_index];
	} else {
		m->submenus.entries[arrow_index]->fn(arrow_index, setup);
		return m->parent;
	}
}

menuitem* menu_left(menuitem* m){
	if(m->parent){
		return m->parent;
	} else {
		return m;
	}
}

void menu_up(menuitem* m){
	uint8_t arrow_index = menu_arrow_index(m);
	if(arrow_index > 0){
		m->submenus.entries[arrow_index]->arrow_flag = 0;
		m->submenus.entries[arrow_index-1]->arrow_flag = 1;
	}
}

void menu_down(menuitem* m){
	uint8_t arrow_index = menu_arrow_index(m);
	if(arrow_index < m->submenus.number - 1){
		m->submenus.entries[arrow_index]->arrow_flag = 0;
		m->submenus.entries[arrow_index+1]->arrow_flag = 1;
	}
}

menuitem* menu_new(char* name, uint8_t numSubmenus, void fn(uint8_t, uint8_t *)){
	menuitem* m = malloc(sizeof(menuitem));
	memset(m, 0, sizeof(menuitem));
	
	m->submenus.entries = malloc(sizeof(menuitem*) * numSubmenus);
	m->submenus.number = numSubmenus;
	m->fn = fn;
	m->name = name;
	
	return m;
}

void menu_player_select(uint8_t choice, uint8_t *setup){
	setup[0] = choice+1;
	can_message_t msg_setup = (can_message_t){
		.id = 0x02,
		.length = 3,
		.data = {	setup[0],  //Players
					setup[1],	//Control type
					setup[2],	//Controller
		},
	};
	can_transmit(msg_setup);
}

void menu_control_select(uint8_t choice, uint8_t *setup){
	setup[1] = choice;
}

void menu_joystick_select(uint8_t choice, uint8_t *setup){
	setup[2] = choice;
}

menuitem* menu_init(){

	menuitem* main_menu = menu_new("Main menu", 2, NULL);
		main_menu->submenus.entries[0] = menu_new("New game", 2, NULL);
			main_menu->submenus.entries[0]->submenus.entries[0] = menu_new("Single player", 0, &menu_player_select); 
			main_menu->submenus.entries[0]->submenus.entries[1] = menu_new("Double player", 0, &menu_player_select); 

		main_menu->submenus.entries[1] = menu_new("Options", 2, NULL);
			main_menu->submenus.entries[1]->submenus.entries[0] = menu_new("Joystick type", 2, NULL);
				main_menu->submenus.entries[1]->submenus.entries[0]->submenus.entries[0] = menu_new("Dualshock3", 0, &menu_joystick_select);
				main_menu->submenus.entries[1]->submenus.entries[0]->submenus.entries[1] = menu_new("Multifunction Card", 0, &menu_joystick_select); 
			main_menu->submenus.entries[1]->submenus.entries[1] = menu_new("Method of control", 2, NULL);
				main_menu->submenus.entries[1]->submenus.entries[1]->submenus.entries[0] = menu_new("Speed", 0, &menu_control_select);
				main_menu->submenus.entries[1]->submenus.entries[1]->submenus.entries[1] = menu_new("Position", 0, &menu_control_select);

	menu_assign_parents_stdArrow(main_menu);
	return main_menu;
}

menuitem* menu2_init(){
	
}

void menu_assign_parents_stdArrow(menuitem* m){
	for(uint8_t idx = 0; idx < m->submenus.number; idx++){
		m->submenus.entries[idx]->parent = m;
		if (idx == 0){
			m->submenus.entries[0]->arrow_flag = 1;	
		}
		if(m->submenus.number > 0){
			menu_assign_parents_stdArrow(m->submenus.entries[idx]);
		}
	}
}


void menu_print(menuitem* m)
{
	OLED_pos(0,0);
	OLED_print_string(m->name);
	OLED_clear_rest_of_line();
	for (uint8_t i = 0; i < m->submenus.number; i++){
		OLED_pos(i+1,0);
		if(m->submenus.entries[i]->arrow_flag){
			OLED_print_string("->");
		}
		else{
			OLED_print_string("  ");
		}		
		OLED_print_string(m->submenus.entries[i]->name);
		OLED_clear_rest_of_line();
	}
}

menuitem* menu_move(menuitem* m, uint8_t* prev_dir, uint8_t *setup)
{	
	switch(Joy_getDirection()){
		case UP:
			if (*prev_dir == NEUTRAL){
				*prev_dir = UP;
				menu_up(m);
			}
			return m;
			break;
		case DOWN:
			if (*prev_dir == NEUTRAL){
				*prev_dir = DOWN;
				menu_down(m);
			}
			return m;
			break;
		case RIGHT:
			if (*prev_dir == NEUTRAL){
				*prev_dir = RIGHT;
				return menu_right(m, setup);
			}
			break;
		case LEFT:
			if (*prev_dir == NEUTRAL){
				*prev_dir = LEFT;
				return menu_left(m);
			}
			break;
		default:
			*prev_dir = NEUTRAL;
			
		break;
	}
	return m;
}


