
#include "menu.h"


void menu_print(int arrow_pos, int menu_size, char* menu_items[])
{
	for(int i = 0; i < menu_size; i++){
		OLED_pos(i,0);
		if(i == arrow_pos){
			OLED_print_string("->");
		}
		else{
			OLED_print_string("  ");
		}
		OLED_print_string(menu_items[i]);
		OLED_clear_rest_of_line();
	}
}

int menu_move_selector(char* menu[], int menu_size){
	int arrow = 0;
	int neutral_counter = 0;
	JOY_direction_t prev_dir = NEUTRAL;
	while(1){
		switch(Joy_getDirection()){
			case UP:
			if ((arrow > 0) & (prev_dir == NEUTRAL)){
				arrow--;
				prev_dir = UP;
			}
			break;
			case DOWN:
			if ((arrow < menu_size-1) & (prev_dir == NEUTRAL)){
				arrow++;
				prev_dir = DOWN;
			}
			break;
			default:
			neutral_counter++;
			if (neutral_counter > 150){
				prev_dir = NEUTRAL;
				neutral_counter = 0;
			}
			break;
		}
		if(!JOY_button(2)){
			while(!JOY_button(2)){}
			return arrow;
		}
		menu_print(arrow, menu_size, menu);
	}
}