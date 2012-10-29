/*
 * pwm.c
 *
 * Created: 25.10.2012 13:37:08
 *  Author: jordifr
 */ 

#include "pwm.h"

void initPWM(){
	ICR1 = 10400;
	OCR1B = CENTRAL_POS;
	TCCR1A |= (1 << COM1B1) | (1 << WGM11);
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (0 << CS12) | (1 << CS11) | (0 << CS10); //Sets mode 14 and preescaler to 8 
	DDRB |= (1 << PB5) | (1 << PB6); //Set as output
	
}

void setPWM(uint8_t pos){
	int16_t t;
	t = (int16_t) (MIN_POS+pos*2.4);
	
	if (t < MIN_POS) t = MIN_POS;
	if (t > MAX_POS) t = MAX_POS;
	
	OCR1B = t;
	printf("pos = %d; OCR = %d;delta = %d; MIN: %d; MAX %d***  DELTA_POS/255 : %d \n\r",pos,OCR1A,DELTA_POS,MIN_POS,MAX_POS, DELTA_POS/255);
}