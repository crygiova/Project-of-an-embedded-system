/*
 * oled.h
 *
 * Created: 27.09.2012 18:01:05
 *  Author: chrisgio
 */ 


#ifndef OLED_H_
#define OLED_H_

#include "globals.h"

void writeDataOLED(uint8_t c); //Sends data to OLED

void writeCommandOLED(uint8_t c); // Send Command to OLED


void clearOLED(); // Blanks the OLED screen
void initOLED(); //Inits OLED at ???

void putcOLED(char c);
void putsOLED(char* s);

void invertModeOLED();
void normalModeOLED();

void putInvertedSOLED(char* s);
void putInvertedCOLED(char c);

//Treats the OLED as a display char of 25 characters long by 8 lines
//It will write from the given position to the end of the line and display
void gotoCharOLED(char line, char pos);

#endif /* OLED_H_ */