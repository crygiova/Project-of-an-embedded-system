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
	DDRB = (1 << DDB2) | (1 << DDB1)  | (1 << DDB0);
	//DDRB &= ~(1 << PB6);
	PORTB |=  (1 << PB0); //Pullup to avoid wrong fallback to slave mode
	//MISO is Overriden as input, TODO: check if it work
	SPCR |=   (1 << SPE) | (1 << MSTR) | (1<<SPR0) ; // fosc/16
	//configured as Master, NOT producing interrupts
	
}

void resetMCP(){
	select_mcp();
	SPDR = MCP_RESET;
     wait_spi();
	deselect_mcp();
	_delay_ms(10);
	//Resets the SPI-CAN controller and waits for it to be ready
}

uint8_t readMCP(char address){
	uint8_t r;
	select_mcp();
	SPDR = MCP_READ;
    wait_spi();
	SPDR = address;
    wait_spi();
	SPDR = MCP_DUMMY;
    wait_spi();
	r = SPDR;
	deselect_mcp();
	return r;
}

void writeMCP(char address, char data){
	select_mcp();
	SPDR = MCP_WRITE;
    wait_spi();
	SPDR = address;
    wait_spi();
	SPDR = data;
    wait_spi();
	deselect_mcp();
}


void requestToSendMCP(char buffer){
	select_mcp();
	switch(buffer) {
		case 0:
			SPDR = MCP_RTS_TX0;
			break;
		case 1:
		    SPDR = MCP_RTS_TX1;
			break;
		case 2:	
		    SPDR = MCP_RTS_TX2;
			break;
	}
	wait_spi();
	deselect_mcp();
}


void bitModifyMCP(char address, char mask, char data){
	select_mcp();
    SPDR = MCP_BITMOD;
    wait_spi();
	SPDR = address;
    wait_spi();
	SPDR = mask;
    wait_spi();
	SPDR = data;
    wait_spi();
	deselect_mcp();
}

uint8_t readStatus(){
	uint8_t r;
	select_mcp();
    SPDR = MCP_READ_STATUS;
    wait_spi();
	SPDR = MCP_DUMMY;
    wait_spi();
	r = SPDR;
	deselect_mcp();
	return r;
}

struct canMessage readRxBufferMCP(char buffer){
	//Adresses are relative to Buffer 0
	struct canMessage m;
	
	select_mcp();
	
	if ( buffer == 0) SPDR = MCP_READ_RX0;
	else SPDR = MCP_READ_RX1;
	wait_spi();
	
	SPDR = MCP_DUMMY;
	wait_spi();
	
	m.id = SPDR<<3; //8 high bits recived and shifted to fit the 11bit format (0x61)
	
	SPDR = MCP_DUMMY;  
	wait_spi();    //Recive lower 3 bits of id
	
	m.id |= (SPDR & 0xE0)>>5;  //Id is received, cleansed and constructed  (0x62)
	
	SPDR = MCP_DUMMY;  
	wait_spi();    //Dummy to read (0x63)
	
	SPDR = MCP_DUMMY;  
	wait_spi();    //Dummy to read (0x64)
	
	SPDR = MCP_DUMMY;  
	wait_spi();    //Reads DLC (size) (0x65)
	
	m.size = SPDR & 0x0F;
	
	//Reading data
	uint8_t c;
	for(c = 0; c < m.size; c++) {
		SPDR = MCP_DUMMY;  
		wait_spi();    //Reads data (0x66..0x6D) 
		m.data[c] = SPDR;
	}
	
	deselect_mcp();
	
	return m;
}


void fillTxBufferMCP(char buffer, struct canMessage m){
	//Adresses are relative to Buffer 0
	select_mcp();
	if ( buffer == 0) SPDR = MCP_LOAD_TX0;
	if ( buffer == 1) SPDR = MCP_LOAD_TX1;
	else SPDR = MCP_LOAD_TX2;
	wait_spi();
	
	uint8_t t;
	
	t = m.id >> 3;
	
	SPDR = t;
	wait_spi();  //sends higher 8 bits of ID to 0x31
	
	t = (m.id << 5) & 0xE0;
	
	SPDR = t;
	wait_spi(); //sends lower 3 bits to higher bits of 0x32
		
	SPDR = MCP_DUMMY;  
	wait_spi();    //Dummy to fill (0x33)
	
	SPDR = MCP_DUMMY;  
	wait_spi();    //Dummy to fill(0x34)
	
	
	SPDR = m.size & 0x0F;  
	wait_spi();    //Sets 0 at the RTR and the proper size at 0x35
	
	//Reading data
	uint8_t c;
	for(c = 0; c < m.size; c++) {
		SPDR = m.data[c];  
		wait_spi();    //fills in data (0x36..0x40) 
	}
	
	deselect_mcp();
}