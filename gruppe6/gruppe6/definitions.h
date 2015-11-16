/*
 * defines.h
 *
 * Created: 12.11.2015 08:56:10
 *  Author: sindrhan
 */ 

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define BAUDRATE 9600

//Game states
#define GAMESTATE settings[0]
#define CTRLTYPE settings[1]
#define JOYSTICKTYPE settings[2]

#define MAINMENU 0
#define CALIBRATE 1
#define PREGAME 2
#define INGAME 3
#define POSTGAME 4

//Joystick types
#define DUALSHOCK3 0
#define MULTICARD 1

//Control methods
#define SPEEDCTRL 0
#define POSCTRL 1

//Calibration status
#define CAL_UNINITIATED 0
#define CAL_INITIATED 1
#define CAL_FINISHED 2

#define IRLIMIT 50
#define SOLENOIDPIN 4

#endif /* DEFINATIONS_H_ */