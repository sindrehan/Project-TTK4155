/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Mega w/ ATmega2560 (Mega 2560), Platform=avr, Package=arduino
*/

#define __AVR_ATmega2560__
#define ARDUINO 165
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define F_CPU 16000000L
#define ARDUINO 165
#define ARDUINO_AVR_MEGA2560
#define ARDUINO_ARCH_AVR
extern "C" void __cxa_pure_virtual() {;}

static int uart_putchar (char c, FILE *stream);
//
//

#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\mega\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"
#include <node2.ino>
#include <MCP2515.h>
#include <Positioncontroller.cpp>
#include <Positioncontroller.h>
#include <node2_can.cpp>
#include <node2_can.h>
#include <node2_i2c.cpp>
#include <node2_i2c.h>
#include <node2_ir.cpp>
#include <node2_ir.h>
#include <node2_mcp2515.cpp>
#include <node2_mcp2515.h>
#include <node2_motorctrl.cpp>
#include <node2_motorctrl.h>
#include <node2_servo.cpp>
#include <node2_servo.h>
#include <node2_spi.cpp>
#include <node2_spi.h>
#include <node2_test.cpp>
#include <node2_test.h>
