/*
 * uart.h
 *
 * Created: 27.09.2012 17:57:44
 *  Author: chrisgio
 */ 


#ifndef UART_H_
#define UART_H_

#include "globals.h"

void initUART(uint16_t ubrr ); //Initializes UART0 at Async 9600

int getC(); //Gets one character from UART

int putC(char data); //Prints one character to UART



#endif /* UART_H_ */