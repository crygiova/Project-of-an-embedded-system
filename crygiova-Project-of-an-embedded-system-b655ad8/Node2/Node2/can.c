/*
 * can.c
 *
 * Created: 11.10.2012 16:51:13
 *  Author: chrisgio
 */ 

//Interrupts
//Control recive , disable all filters and masks
//Set mode

#include "can.h"


volatile uint8_t flagMCP; //FLAG for MCP 

void initCAN(enum canMode mode){
	
	uint8_t t;
	switch (mode){
		case(NORMAL):
			t = 0x00;			
			break;
		case(SLEEP):
			t = 0x20;
			break;
		case(LOOPBACK):
			t = 0x40;			
			break;
		case(LISTEN):
			t = 0x60;
			break;		
		case(CONFIG):
			t = 0x80;
			break;
	};
	
	writeMCP(MCP_CANCTRL,t); //Sets mode
	writeMCP(MCP_RXB0CTRL, 0b01100000); //Disable all Filters buffer 0 //Todo, by names
	writeMCP(MCP_RXB1CTRL, 0b01100000); //Disable all Filters buffer 1
	writeMCP(MCP_CANINTF,0x00); //Clear Pending Interrupts
	writeMCP(MCP_CANINTE, 0x1F); //Enable reception interrupts on both buffers
}