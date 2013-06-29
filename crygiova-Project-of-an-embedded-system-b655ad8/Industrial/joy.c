/*
 * joy.c
 *
 * Created: 27.09.2012 17:50:17
 *  Author: chrisgio
 */ 

#include "globals.h"
#include "joy.h"

volatile uint8_t flagJoyButton = 0; //Initialize flag for joy button
struct joypos_t mPoint; //Will be initialized in runtime

struct slidepos_t slide1Point; //Will be initialized in runtime
struct slidepos_t slide2Point; //Will be initialized in runtime


void joyInit(){
	mPoint.x = ADC_read(X_AXIS);
	mPoint.y = ADC_read(Y_AXIS);
}

struct joypos_t getJoyPosition(){
	struct joypos_t r;
	r.x = ADC_read(X_AXIS);
	r.y = ADC_read(Y_AXIS);
	return r;	
}


struct slidepos_t getSlidePosition(uint8_t number)//returns the slider position
{
	struct slidepos_t r;
	if(number==1)//if number is 1 we read the first slider
	{
		r.x=ADC_read(L_SLIDER);
	}
	else//we read the second one
	{
		r.x=ADC_read(R_SLIDER);
	}	
	return r;
}

enum joydir_t getJoyDirection(){
	struct joypos_t r;
    r = getJoyPosition();
	if (abs(r.x-mPoint.x) < JOYSTICK_DEADZONE && abs(r.y-mPoint.y) < JOYSTICK_DEADZONE) return CENTER;
	else {
		if (abs(r.x-mPoint.x) < JOYSTICK_DEADZONE && !abs(r.y-mPoint.y) < JOYSTICK_DEADZONE) {
			if (r.y > mPoint.y) return TOP;
			else return BOTTOM;
		}
		if (!abs(r.x-mPoint.x) < JOYSTICK_DEADZONE && abs(r.y-mPoint.y) < JOYSTICK_DEADZONE) {
			if (r.x > mPoint.x) return RIGHT;
			else return LEFT;
		} 
		if (r.x < mPoint.x && r.y < mPoint.y) return LEFT_BOTTOM; 
		if (r.x < mPoint.x && r.y > mPoint.y) return LEFT_TOP;
		if (r.x > mPoint.x && r.y < mPoint.y) return RIGHT_BOTTOM;
		if (r.x > mPoint.x && r.y > mPoint.y) return RIGHT_TOP;
	}
	
	return CENTER; //In case of error return inhert NEVER USED
}



	
	void printdir(enum joydir_t d) {
		switch (d){
			case TOP: printf("TOP \r\n"); break;
			case BOTTOM: printf("BOTTOM \r\n"); break;
			case LEFT: printf("LEFT \r\n"); break;
			case RIGHT: printf("RIGHT \r\n"); break;
			case RIGHT_BOTTOM: printf("RIGHT_BOTTOM \r\n"); break;
			case RIGHT_TOP: printf("RIGHT_TOP \r\n"); break;
			case LEFT_TOP: printf("LEFT_TOP \r\n"); break;
			case LEFT_BOTTOM: printf("LEFT_BOTTOM \r\n"); break;
			case CENTER: printf("SENTRUM \r\n"); break;	
		}	
		
	}
