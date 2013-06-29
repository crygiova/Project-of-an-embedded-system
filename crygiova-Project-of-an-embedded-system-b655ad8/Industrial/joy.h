/*
 * joy.h
 *
 * Created: 27.09.2012 17:50:31
 *  Author: chrisgio
 */ 


#ifndef JOY_H_
#define JOY_H_

struct joypos_t {  //Structure to keep joystick positions
	uint8_t x;
	uint8_t y;	
};

struct slidepos_t{ //structure that define the position of one slider
	uint8_t x;
};

enum joydir_t {LEFT_BOTTOM, LEFT_TOP, RIGHT_BOTTOM, RIGHT_TOP,TOP, BOTTOM, LEFT, RIGHT, CENTER}; //Enum to give directions in a nonquantitative way

extern struct joypos_t mPoint; //Keeps central point

extern struct slidepos_t slide1Point; //Keeps central point
extern struct slidepos_t slide2Point;

#define JOYSTICK_DEADZONE 25 //Offset for dead zone

	void joyInit(); //Initialization and calib of joy
	struct joypos_t getJoyPosition(); //Returns position of the joystick
	enum joydir_t getJoyDirection(); //Returns direction in non quantitative way
	void printdir(enum joydir_t d); //Prints dir through UART
	
	void slideInit();//init of the slider
	struct slidepos_t getSlidePosition(uint8_t number);//returns the slider position




#endif /* JOY_H_ */