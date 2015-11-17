
#ifndef TEST_H_
#define TEST_H_

#include <avr/io.h>
#include <util/delay.h>

#include "adc_driver.h"
#include "joystick.h"
#include "oled_driver.h"
#include "menu.h"
#include "mcp2515_driver.h"
#include "can.h"


void test_adc(void);
void test_joystick(void);
//void test_oled_menu(void);
void test_mcp(void);
void test_can(void);

#endif /* TEST_H_ */