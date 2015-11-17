
#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_

#include <avr/io.h>
#include <stdio.h>
#include "joystick.h"

void OLED_init(void);
void OLED_command(uint8_t c);
void OLED_data(uint8_t c);
void OLED_go_to_page(uint8_t page);
void OLED_clear_page(uint8_t page);
void OLED_reset(void);
void OLED_home(void);
void OLED_pos(uint8_t page, uint8_t column);
void OLED_go_to_col(uint8_t column);
void OLED_clear_rest_of_line(void);
void OLED_print(char character);
void OLED_print_string(char string[]);

#endif /* OLED_DRIVER_H_ */