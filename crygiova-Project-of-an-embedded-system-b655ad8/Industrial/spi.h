/*
 * spi.h
 *
 * Created: 04.10.2012 12:16:16
 *  Author: chrisgio
 */ 

 
 

#ifndef SPI_H_
#define SPI_H_

#include "globals.h"

#define select_mcp() PORTB &= ~(1<<PB4);
#define deselect_mcp() PORTB |= (1<<PB4);
#define wait_spi() while(!(SPSR & (1<<SPIF)));

// Define MCP2515 register addresses

#define MCP_RXF0SIDH	0x00
#define MCP_RXF0SIDL	0x01
#define MCP_RXF0EID8	0x02
#define MCP_RXF0EID0	0x03
#define MCP_RXF1SIDH	0x04
#define MCP_RXF1SIDL	0x05
#define MCP_RXF1EID8	0x06
#define MCP_RXF1EID0	0x07
#define MCP_RXF2SIDH	0x08
#define MCP_RXF2SIDL	0x09
#define MCP_RXF2EID8	0x0A
#define MCP_RXF2EID0	0x0B
#define MCP_CANSTAT		0x0E
#define MCP_CANCTRL		0x0F
#define MCP_RXF3SIDH	0x10
#define MCP_RXF3SIDL	0x11
#define MCP_RXF3EID8	0x12
#define MCP_RXF3EID0	0x13
#define MCP_RXF4SIDH	0x14
#define MCP_RXF4SIDL	0x15
#define MCP_RXF4EID8	0x16
#define MCP_RXF4EID0	0x17
#define MCP_RXF5SIDH	0x18
#define MCP_RXF5SIDL	0x19
#define MCP_RXF5EID8	0x1A
#define MCP_RXF5EID0	0x1B
#define MCP_TEC			0x1C
#define MCP_REC			0x1D
#define MCP_RXM0SIDH	0x20
#define MCP_RXM0SIDL	0x21
#define MCP_RXM0EID8	0x22
#define MCP_RXM0EID0	0x23
#define MCP_RXM1SIDH	0x24
#define MCP_RXM1SIDL	0x25
#define MCP_RXM1EID8	0x26
#define MCP_RXM1EID0	0x27
#define MCP_CNF3		0x28
#define MCP_CNF2		0x29
#define MCP_CNF1		0x2A
#define MCP_CANINTE		0x2B
#define MCP_CANINTF		0x2C
#define MCP_EFLG		0x2D
#define MCP_TXB0CTRL	0x30
#define MCP_TXB1CTRL	0x40
#define MCP_TXB2CTRL	0x50
#define MCP_TXB0SIDH	0x31
#define MCP_TXB2SIDH	0x41
#define MCP_TXB3SIDH	0x51
#define MCP_RXB0CTRL	0x60
#define MCP_RXB0SIDH	0x61
#define MCP_RXB1CTRL	0x70
#define MCP_RXB1SIDH	0x71



// Define SPI Instruction Set

#define MCP_WRITE		0x02 
#define MCP_READ		0x03 
#define MCP_BITMOD		0x05 
#define MCP_LOAD_TX0	0x40 
#define MCP_LOAD_TX1	0x42 
#define MCP_LOAD_TX2	0x44 
#define MCP_RTS_TX0		0x81
#define MCP_RTS_TX1		0x82
#define MCP_RTS_TX2		0x84
#define MCP_RTS_ALL		0x87
#define MCP_READ_RX0	0x90 
#define MCP_READ_RX1	0x94
#define MCP_READ_STATUS	0xA0
#define MCP_RX_STATUS	0xB0
#define MCP_RESET		0xC0

#define MCP_DUMMY		0x00

#define MAX_CAN_DATA_SIZE 8

struct canMessage {
	uint16_t id;
	uint8_t size;
	uint8_t data[MAX_CAN_DATA_SIZE]; //Todo: move to can file
};


void initSPI();
void resetMCP();
uint8_t readMCP(char address);
struct canMessage readRxBufferMCP(char buffer);
void writeMCP(char address, char data);
void requestToSendMCP(char buffer);
void bitModifyMCP(char address, char mask, char data);
uint8_t readStatus();
void fillTxBufferMCP(char buffer, struct canMessage m);


#endif /* SPI_H_ */