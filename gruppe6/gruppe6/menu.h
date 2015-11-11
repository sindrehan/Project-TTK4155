
#ifndef MENU_H_
#define MENU_H_

#include "oled_driver.h"
#include "can.h"
#include <string.h>
#include <stdlib.h>


//void menu_print(int arrow_pos, char* menu_items[]);
//int menu_move_selector(char* menu[]);

typedef struct menuitem {
	char* name;
	uint8_t arrow_flag;
	struct submenus{
		uint8_t		number;
		struct menuitem**	entries;
	} submenus;
	struct menuitem*	parent;
	void (*fn)(uint8_t, can_message_t*);
} menuitem;

uint8_t menu_arrow_index(menuitem* m);
menuitem* menu_right(menuitem* m, can_message_t* setup);
menuitem* menu_left(menuitem* m);
void menu_up(menuitem* m);
void menu_down(menuitem* m);
menuitem* menu_new(char* name, uint8_t numSubmenus, void fn(uint8_t, can_message_t*));
menuitem* menu_init();
void menu_assign_parents_stdArrow(menuitem* base);
void menu_print(menuitem* m);
menuitem* menu_move(menuitem* m, uint8_t* prev_dir, can_message_t* setup);


#endif /* MENU_H_ */