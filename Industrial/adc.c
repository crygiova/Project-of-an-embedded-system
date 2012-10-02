/*
 * adc.c
 *
 * Created: 27.09.2012 17:40:53
 *  Author: chrisgio
 */ 

#include "globals.h"
#include "adc.h"

uint8_t resultADC;
uint8_t flagADC;

volatile char* extADC = 0x1442;

void readADC(enum channelsADC channel){
	switch(channel){
		case Y_AXIS:
			*extADC = 0x04;
			break;
		case X_AXIS:
			*extADC = 0x05;
			break;
		case L_SLIDER:
			*extADC = 0x06;
			break; 
		case R_SLIDER: 
			*extADC = 0x07;
			break;
		default:
			*extADC = 0x00;
			break;
	}
	//_delay_ms(100); //TODO: interrupt
	//result = *extADC;
	}

uint8_t ADC_read(enum channelsADC channel){
	readADC(channel);
	while(!flagADC); //TODO: Make it less pooling-style
	flagADC = 0;
	return resultADC;
}