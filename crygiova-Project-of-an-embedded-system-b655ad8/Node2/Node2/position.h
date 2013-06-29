/*
 * position.h
 *
 * Created: 12.11.2012 20:31:44
 *  Author: jordifr
 */ 


#include "globals.h"

#ifndef POSITION_H_
#define POSITION_H_

#define DEAD_ZONE_JOY 25

extern int16_t currentPos;
extern int16_t newPos;

void initMotor();
void updatePosMotor();
int16_t readEncoder();

#endif /* POSITION_H_ */