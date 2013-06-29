/*
 * globals.h
 *
 * Created: 31.08.2012 14:35:11
 *  Author: jordifr
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_


#define F_CPU 4000000UL
#define BAUD 9600
#define UBBR 27

//define pin

#include <avr/io.h>
#include "util/delay.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdlib.h>


#include "uart.h"
#include "spi.h"
#include "can.h"
#include "pwm.h"
#include "adc.h"

extern volatile uint8_t flagMCP; 

//Macros

#define reload() PORTF |= (1 << PF2);
#define shot() PORTF &= ~(1 << PF2);

//MJ1

#define backwardMotor() PORTA |= (1 << PA3);
#define forwardMotor() PORTA &= ~(1 << PA3);

#define enableMotor() PORTA |= (1 << PA4);
#define disableMotor() PORTA &= ~(1 << PA4);

#define setSel() PORTA |= (1 << PA5);
#define clearSel() PORTA &= ~(1 << PA5);

#define setReset() PORTA |= (1 << PA6);
#define clearReset() PORTA &= ~(1 << PA6);

#define setOE() PORTA |= (1 << PA7);
#define clearOE() PORTA &= ~(1 << PA7);

struct joypos_t {  //Structure to keep joystick positions
	uint8_t x;
	uint8_t y;	
};


enum joydir_t {LEFT_BOTTOM, LEFT_TOP, RIGHT_BOTTOM, RIGHT_TOP,TOP, BOTTOM, LEFT, RIGHT, CENTER}; //Enum to give directions in a nonquantitative way

extern struct joypos_t mPoint; //Keeps central point

extern int score;

#endif /* GLOBALS_H_ */