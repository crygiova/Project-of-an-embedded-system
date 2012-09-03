/*
 * UARTSender.c
 *
 * Created: 31.08.2012 14:21:15
 *  Author: jordifr
 */ 

#include <avr/io.h>
#include "globals.h"
#define F_CPU 4915200UL
#include <util/delay.h>
#include <stdio.h>
//#include "drvUART.h"

int getC()
{
	uint8_t c;
	while( !(UCSR0A & 1 << RXC0) );
	c = UDR0;
	//while( !(UCSR0A & 1 << UDRE0) );
	return c;
}

int putC(uint8_t data){
	while( !(UCSR0A & 1 << UDRE0) );
	UDR0 = data;
	while( !(UCSR0A & 1 << TXC0) );
	return 0;
}


void initUART(uint16_t ubrr ){
	
	//Init clock generator reg
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;
	//UCSR0A = 0b00000000 //TODO: Rx & Tx "polling"
	UCSR0B = 0b00011000;
	UCSR0C = 0b10000110;
	
	
	//Enable Rx and Tx
	//UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	
	//Set format
	//UCSR0C = (1<<URSEL0)|(1<<USBS0) | (3 << UCSZ01);
	
	fdevopen(putC,getC);
}



int main(void)
{
	initUART(31);
	PORTA = 0xFF;
	unsigned char c = 'A';
    while(1)
    {
		//c = getC();
		putC('A');
		//printf("Hello World: %d \r\n", 42);
		//if (c > 'Z') c = 'A';
        //TODO:: Please write your application code
		//_delay_ms(1);
		PORTA = ~PORTA;
		 
    }
}