/*
 * utils.c
 *
 * Created: 27.09.2012 18:06:09
 *  Author: chrisgio
 */ 


#include "utils.h"

void testLatch()
{
	DDRA = 0xFF;
	DDRE = 0xFF;
	ADDRESS_LOW = 0x55;
	PORT_E.b1 = 1;
	_delay_ms(10);
	PORT_E.b1 = 0;
	ADDRESS_LOW = 0x00;
}

void SRAM_test(void)
{
	// Start address for the SRAM
	volatile char *ext_ram = (char *) 0x1800;
	
	unsigned int i, werrors, rerrors;
	werrors = 0;
	rerrors = 0;
	unsigned char testvalue;

	printf("Starting SRAM test...\r\n");

	for (i = 0; i < 0x800; i++) {
		//_delay_ms(1);
		testvalue = ~(i % 256);
		ext_ram[i] = testvalue;
		//printf("WRITE: current i: %d \r\n",i);
		if (ext_ram[i] != testvalue) {
			printf("SRAM error (write phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
			werrors++;
		} else {
			//printf("SRAM WRITE OK \r\n "); 
		}
	}

	for (i = 0; i < 0x800; i++) {
		//_delay_ms(1);
		testvalue = ~(i % 256);
		//printf("READ: current i: %d \r\n",i);
  		if (ext_ram[i] != testvalue) {
			printf("SRAM error (read phase): ext_ram[%d] = %02X (should be %02X)\r\n", i, ext_ram[i], testvalue);
			rerrors++;
		} else {
			//printf("SRAM READ OK \r\n "); 
		}
	}
	printf("SRAM test completed with %d errors in write phase and %d errors in read phase\r\n", werrors, rerrors);
}




void GAL_test(void* start, void* stop){
	volatile char* access = (char *) start;
	while(access != (char* ) stop ) {
		*access = 0x42;
		++access;
		_delay_ms(10);
	}
		
	
}