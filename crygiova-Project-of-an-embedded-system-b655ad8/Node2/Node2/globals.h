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



#include <avr/io.h>
#include "util/delay.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdlib.h>


#include "uart.h"
#include "spi.h"
#include "can.h"

extern volatile uint8_t flagMCP; 


struct joypos_t {  //Structure to keep joystick positions
	uint8_t x;
	uint8_t y;	
};


enum joydir_t {LEFT_BOTTOM, LEFT_TOP, RIGHT_BOTTOM, RIGHT_TOP,TOP, BOTTOM, LEFT, RIGHT, CENTER}; //Enum to give directions in a nonquantitative way

extern struct joypos_t mPoint; //Keeps central point


#endif /* GLOBALS_H_ */