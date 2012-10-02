/*
 * oled.c
 *
 * Created: 27.09.2012 18:00:53
 *  Author: chrisgio
 */ 

#include "oled.h"
#include "font_5x7.h"

volatile char* extDataOled = 0x1242; //Adress for the Data reg of the OLED DC=0       0b0001 0010 0100 0010
volatile char* extCommandOled = 0x1001; //Adress for the Command reg of the OLED DC=1 0b0001 0000 0000 0001

void writeDataOLED(uint8_t c){
	*extDataOled = c;
}

void writeCommandOLED(uint8_t c){
	*extCommandOled = c;
}

void initOLED()
{
    writeCommandOLED(0xae); // display off
    writeCommandOLED(0xa1); //segment remap
    writeCommandOLED(0xda); //common pads hardware: alternative
    writeCommandOLED(0x12);
    writeCommandOLED(0xc8); //common output scan direction:com63~com0
    writeCommandOLED(0xa8); //multiplex ration mode:63
    writeCommandOLED(0x3f);
    writeCommandOLED(0xd5); //display divide ratio/osc. freq. mode
    writeCommandOLED(0x80);
    writeCommandOLED(0x81); //contrast control
    writeCommandOLED(0x50);
    writeCommandOLED(0xd9); //set pre-charge period
    writeCommandOLED(0x21);
    writeCommandOLED(0x20); //Set Memory Addressing Mode
    writeCommandOLED(0x00); // horizontal
    writeCommandOLED(0xdb); //VCOM deselect level mode
    writeCommandOLED(0x30);
    writeCommandOLED(0xad); //master configuration
    writeCommandOLED(0x00);

    //oled_home();
    writeCommandOLED(0x21); //Set column
	writeCommandOLED(0x00);
	writeCommandOLED(0x7F);
	
	writeCommandOLED(0x22); //Set row
	writeCommandOLED(0x00);
	writeCommandOLED(0x07);
	
	writeCommandOLED(0x40); //Set start line to 0th

    writeCommandOLED(0xa4); //out follows RAM content
    writeCommandOLED(0xa6); //set normal display
    writeCommandOLED(0xaf); // display on
	
	clearOLED();
	
	
}


void invertModeOLED() {
	writeCommandOLED(0xa7);	
}

void normalModeOLED() {
	writeCommandOLED(0xa6);	
}

//Treats the OLED as a display char of 25 characters long by 8 lines
//It will write from the given position to the end of the line and display
void gotoCharOLED(char line, char pos){
	writeCommandOLED(0x21);
	writeCommandOLED(pos*5);
	writeCommandOLED(0x7F);
	
	writeCommandOLED(0x22);
	writeCommandOLED(line);
	writeCommandOLED(0x07);
}

void gotoPosOLED(char x, char y){
	writeCommandOLED(0x21);
	writeCommandOLED(x);
	writeCommandOLED(0x7F);
	
	writeCommandOLED(0x22);
	writeCommandOLED(y);
	writeCommandOLED(0x07);
}

void putsOLED(char* s){
	uint8_t counter;
	for(counter = 0; s[counter] !=  '\0'; counter++) putcOLED(s[counter]);
}

void putInvertedSOLED(char* s){
	uint8_t counter;
	for(counter = 0; s[counter] !=  '\0'; counter++) putInvertedCOLED(s[counter]);
}

void putcOLED(char c){
	uint8_t counter;
	for(counter = 0; counter < 5; counter++) writeDataOLED(pgm_read_byte(&(myfont[c-32][counter]))); //-32 is to compensate for the offset between our fontfile and the true ascii table
}

void putInvertedCOLED(char c){
	uint8_t counter;
	for(counter = 0; counter < 5; counter++) writeDataOLED(~pgm_read_byte(&(myfont[c-32][counter]))); 
}

void clearOLED(){
	gotoPosOLED(0,0);
	uint16_t i;
	for(i = 0; i < 128*8; i++) writeDataOLED(0x00);
	gotoPosOLED(0,0);
}