
#ifndef MENU_H_
#define MENU_H_

#include "oled_driver.h"

void menu_print(int arrow_pos, char* menu_items[]);
int menu_move_selector(char* menu[]);


#endif /* MENU_H_ */