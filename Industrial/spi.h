/*
 * spi.h
 *
 * Created: 04.10.2012 12:16:16
 *  Author: chrisgio
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "globals.h"

//Comands for the SPI interface
#define READ_STATUS 0b10100000;


void initSPI();
void writeSPI(char data);
uint8_t readSPI();
uint8_t readCANCTL();

void setClockSpeedSPI();


#endif /* SPI_H_ */