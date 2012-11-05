/*
 * adc.h
 *
 * Created: 02.11.2012 14:26:50
 *  Author: chrisgio
 */ 


#ifndef ADC_H_
#define ADC_H_

#define GOAL_THRESH 10

#include "globals.h"

extern uint8_t ADCReady;
extern char inScore;


void initADC();
short readADC();
short averageADC(char times);


#endif /* ADC_H_ */