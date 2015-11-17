
#ifndef MENU_H_
#define MENU_H_

#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

#include "oled_driver.h"
#include "can.h"
#include "definitions.h"
#include "fsm.h"

typedef struct menuitem {
	char* name;
	uint8_t arrow_flag;
	struct submenus{
		uint8_t		number;
		struct menuitem**	entries;
	} submenus;
	struct menuitem*	parent;
	void (*fn)(uint8_t, uint8_t *);
} menuitem;

uint8_t menu_arrow_index(menuitem* m);
menuitem* menu_right(menuitem* m, uint8_t *setup);
menuitem* menu_left(menuitem* m);
void menu_up(menuitem* m);
void menu_down(menuitem* m);
menuitem* menu_new(char* name, uint8_t numSubmenus, void fn(uint8_t, uint8_t *));
menuitem* menu_init();
void menu_assign_parents_stdArrow(menuitem* base);
void menu_print_mainmenu(menuitem* m);
menuitem* menu_move(menuitem* m, uint8_t* prev_dir, uint8_t *settings);

void menu_new_game(uint8_t choice, uint8_t *setup);
void menu_control_select(uint8_t choice, uint8_t *setup);
void menu_joystick_select(uint8_t choice, uint8_t *setup);

void menu_print_ingame(uint8_t *time);
void menu_print_calibrate(uint8_t cal_status);

void menu_print_pregame(void);
void menu_print_postgame(uint8_t *time);


#endif /* MENU_H_ */