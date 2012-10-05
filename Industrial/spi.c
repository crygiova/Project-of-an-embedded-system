/*
 * spi.c
 *
 * Created: 04.10.2012 12:16:02
 *  Author: chrisgio
 */ 


#include "spi.h"

void initSPI(){
	//Setting pins and directions 
	//MOSI, SCK, !SS as output
	DDRB |= (1 << PB7) | (1 << PB5)  | (1 << PB4);
	PORTB |=  (1 << PB4); //Pullup to avoid wrong fallback to slave mode
	//MISO is Overriden as input, TODO: check if it work
	SPCR |=   (1 << SPE) | (1 << MSTR) | (1<<SPR0);
	//configured as Master, NOT producing interrupts and Mode 1;
	
}

void writeSPI(char data){
   //Lower !SS
   PORTB &= ~(1<<PB4);
      
   SPDR = data;
   
   while (!((SPSR) & (1 << SPIF))); //TODO: Make it interrupt based maybe
   
   //Rise !SS
   PORTB |= (1<<PB4);	 
}


uint8_t readCANCTL(){
	
   PORTB &= ~(1<<PB4);
      
   SPDR = 0x03;
   while (!((SPSR) & (1 << SPIF))); //TODO: Make it interrupt based maybe
   
   SPDR = 0x0F;
   while (!((SPSR) & (1 << SPIF))); //TODO: Make it interrupt based maybe
   
   while (!((SPSR) & (1 << SPIF))); //TODO: Make it interrupt based maybe
   
   
   //Rise !SS
   PORTB |= (1<<PB4);
   
   return SPDR;	
}

uint8_t readSPI(){
   uint8_t r;
   
   //Lower !SS
   PORTB &= ~(1<<PB4);
      
   SPDR = 0x42; //Dummy write to enable SCLK
      
   while (!(SPSR) & (1 << SPIF)); //TODO: Make it interrupt based maybe
   
   r = SPDR; //Reads the SPI recive buffer
   
   //Rise !SS
   PORTB |= (1<<PB4);	 
   
   return r;
}

void setClockSpeedSPI(){
	 PORTB &= ~(1<<PB4);
	 /*SPDR = 0b00000101; //Modify Bit Command
	 while (!(SPSR) & (1 << SPIF)); //TODO: Make it interrupt based maybe
	
	 SPDR = 0x0F; //Set Adress to CANCTRL
	 while (!(SPSR) & (1 << SPIF)); //TODO: Make it interrupt based maybe
	 
	 SPDR = 0b00000011; //Mask
	 while (!(SPSR) & (1 << SPIF)); //TODO: Make it interrupt based maybe

	SPDR = 0b00000000; //Data
	 while (!(SPSR) & (1 << SPIF)); //TODO: Make it interrupt based maybe
    */
	 
	 SPDR = 0b00000010;
	 while (!(SPSR) & (1 << SPIF)); //TODO: Make it interrupt based maybe
	 
	 SPDR = 0x0F;
	 while (!(SPSR) & (1 << SPIF)); //TODO: Make it interrupt based maybe
	 
	 SPDR=0b00000100;
	 while (!(SPSR) & (1 << SPIF)); //TODO: Make it interrupt based maybe
	 
	 
	PORTB |= (1<<PB4);
}