/*
 * uart.c
 *
 * Created: 27.09.2012 17:57:29
 *  Author: chrisgio
 */ 


#include "uart.h"

void initUART(uint16_t ubrr ){
	
	//Init clock generator reg
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;
	//UCSR0A = 0b00000000 //TODO: Rx & Tx "polling"
	UCSR0B = 0b00011000;
	UCSR0C = 0b10000110;
	
	fdevopen(putC,getC);
}

int getC()
{
	uint8_t c;
	while( !(UCSR0A & 1 << RXC0) );
	c = UDR0;
	return c;
}

int putC(char data){
	while( !(UCSR0A & 1 << UDRE0) );
	UDR0 = data;
	while( !(UCSR0A & 1 << TXC0) );
	return 0;
}