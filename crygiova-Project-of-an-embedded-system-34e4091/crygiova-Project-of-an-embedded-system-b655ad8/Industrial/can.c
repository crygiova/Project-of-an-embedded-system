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
	writeMCP(MCP_CANINTE, 0x1C); //Enable reception interrupts on both buffers
}


void sendCANJoy(uint8_t buffer, struct joypos_t p, enum joydir_t d){
	struct canMessage message;
	
	message.id = JOY_MESSAGE;
	message.size = 4;
	
	message.data[0] = p.x; //X component of the joy
	message.data[1] = p.y; //Y component of the joy
	message.data[2] = (uint8_t) d; //Direction according to the enum
	message.data[3] = CAN_TERMINATION;
	
	printf ("Joy X: %d, Joy Y: %d Joy: Pos: %d \r\n", (uint8_t) message.data[0], (uint8_t) message.data[1], (uint8_t) message.data[2]);  
	
	fillTxBufferMCP(buffer,message);
	requestToSendMCP(buffer); 
		
}