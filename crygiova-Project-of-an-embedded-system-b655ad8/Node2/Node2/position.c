/*
 * position.c
 *
 * Created: 12.11.2012 20:31:31
 *  Author: jordifr
 */ 



#include "position.h"


extern int16_t currentPos;
extern int16_t newPos;



/*void setEngineVoltageJoy(unsigned char axis){
	char msg[3];
	msg[0] = 0x50;
	msg[1] = 0x00; 
	if (abs(128-axis) > 30) {
		enableMotor();
		msg[2] = (abs(128-axis)-2);//;*2;
		if (axis > 128){
		     forwardMotor();
//			 printf("FORWARD \r\n");	
		} else {
			backwardMotor();
//			 printf("BACKWARD \r\n");	
		}					
		TWI_Start_Transceiver_With_Data(msg, 3);
	}
	else {
		disableMotor();
	}
	
}


void setEngineVoltage(unsigned char speed){
		char msg[3]; 
		msg[0] = 0x50;
		msg[1] = 0x00;
		msg[2] = speed; 
		TWI_Start_Transceiver_With_Data(msg, 3);
}*/

void speedMotor(char speed){
	char msg[3]; 
	msg[0] = 0x50;
	msg[1] = 0x00;
	msg[2] = speed; 
	TWI_Start_Transceiver_With_Data(msg, 3);
}

void initMotor(){
	char msg[3]; 
	msg[0] = 0x50;
	msg[1] = 0x00;
	msg[2] = 160; 
	TWI_Start_Transceiver_With_Data(msg, 3);
	forwardMotor();
	enableMotor();
	_delay_ms(500);
	disableMotor();
	
	currentPos = 0;
	newPos = 0; //TODO
}

int16_t readEncoder(){
	int16_t encoder;
	clearOE();
	clearSel();
	_delay_ms(23);
	encoder = reverse(PINC)<< 8;
	setSel();
	_delay_ms(23);
	encoder |= reverse(PINC);
	setOE();
	clearReset();
	_delay_ms(1);
	setReset();
	return encoder;
}


void updatePos(uint8_t joy){
	currentPos = current + readEncoder();
	
    if ((joy - 128) > DEAD_ZONE_JOY)
	{
		newPos = (joy*3)+currentPos;
		if (newPos > 10000) newPos = 10000;
	}
	else 
	if ((joy - 128) < -DEAD_ZONE_JOY)
	{
		newPos = -(joy*3)+currentPos;
		if (newPos < 0) newPos = 0;
	}
	
}



void moveMotor() {
	if (currentPos < newPos) forwardMotor();
	else backwardMotor();
	
	char speed = abs(currentPos-newPos)/39;
	speedMotor(speed);
	
	enableMotor();
}





