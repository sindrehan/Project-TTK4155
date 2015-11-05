
#ifndef MENU_H_
#define MENU_H_

#include "oled_driver.h"

void menu_print(int arrow_pos, int menu_size, char* menu_items[]);
int menu_move_selector(char* menu[], int menu_size);


#endif /* MENU_H_ */