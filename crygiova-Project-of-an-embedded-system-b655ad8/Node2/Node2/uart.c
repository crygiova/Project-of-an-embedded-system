/*
 * uart.c
 *
 * Created: 27.09.2012 17:57:29
 *  Author: chrisgio
 */ 


#include "uart.h"

void initUART(uint16_t ubrr ){
	
	//Init clock generator reg
	UBRR1H = (unsigned char) (ubrr >> 8);
	UBRR1L = (unsigned char) ubrr;
	//UCSR0A = 0b00000000 //TODO: Rx & Tx "polling"
	UCSR1B = 0b00011000;
	UCSR1C = 0b10000110;	
	fdevopen(putC,getC);
}

int getC()
{
	uint8_t c;
	while( !(UCSR1A & 1 << RXC1) );
	c = UDR1;
	return c;
}

int putC(char data){
	while( !(UCSR1A & 1 << UDRE1) );
	UDR1 = data;
	while( !(UCSR1A & 1 << TXC1) );
	return 0;
}