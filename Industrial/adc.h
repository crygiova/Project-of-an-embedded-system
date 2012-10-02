/*
 * adc.h
 *
 * Created: 27.09.2012 17:41:09
 *  Author: chrisgio
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "globals.h"

extern uint8_t resultADC;
extern uint8_t flagADC;
enum channelsADC {X_AXIS, Y_AXIS, L_SLIDER, R_SLIDER};

void readADC(enum channelsADC channel);

uint8_t ADC_read(enum channelsADC channel);




#endif /* ADC_H_ */