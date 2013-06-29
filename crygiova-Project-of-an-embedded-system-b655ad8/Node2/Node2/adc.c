/*
 * adc.c
 *
 * Created: 02.11.2012 14:26:30
 *  Author: chrisgio
 */ 


#include "adc.h"


uint8_t ADCReady = 0;
char inScore=0;
int score=0;

void initADC(){
	ADMUX |=  (1 << REFS0) | (1 << REFS1); //We will be using Vcc as a + reference and chanel 0 (ADC0 / PF0)
    ADCSRA |= (1 << ADEN) |(1 << ADIE);
	DDRF &= ~(1<<PF0); //Set PF1 as Input
	
}

short readADC(){
	short r;
	ADCSRA |= (1 << ADSC);
	while ( !ADCReady ); //Wait while the flag is 0
	ADCReady = 0;
	r = ADC; //(ADCH << 8) | ADCL;
	return r;
}


short averageADC(char times){
	char i;
	short acum = 0;
	for ( i = 0; i < times; i++) {
		acum+=readADC();
		_delay_ms(5);
	}
	acum = acum/times;
	if (!inScore && acum < GOAL_THRESH){
		++score;
		inScore = 1;
	} else if (inScore && acum >= GOAL_THRESH) {inScore = 0;}
	return acum;
}