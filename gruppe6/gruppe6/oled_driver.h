
#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_

#include <avr/io.h>
#include <stdio.h>
#include "joystick.h"

void OLED_init();
void OLED_command(char c);
void OLED_data(char c);
void OLED_go_to_page(char page);
void OLED_clear_page(char page);
void OLED_reset();
void OLED_home();
void OLED_pos(char page, char column);
void OLED_go_to_col(char column);
void OLED_clear_rest_of_line();
void OLED_print(char character);
void OLED_print_string(char string[]);

#endif /* OLED_DRIVER_H_ */