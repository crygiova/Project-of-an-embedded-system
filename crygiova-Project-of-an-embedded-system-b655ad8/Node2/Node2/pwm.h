/*
 * pwm.c
 *
 * Created: 25.10.2012 13:37:20
 *  Author: jordifr
 */ 

#ifndef PWM_H_
#define PWM_H_

#include "globals.h"


//Constants for PWM
#define MIN_POS 461
#define CENTRAL_POS 768
#define MAX_POS 1075
#define DELTA_POS (MAX_POS - MIN_POS)



void initPWM();
void setPWM(uint8_t pos);

#endif