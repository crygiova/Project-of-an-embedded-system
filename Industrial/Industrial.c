/*
 * Industrial.c
 *
 * Created: 10.09.2012 13:23:14
 *  Author: jordifr
 */ 

#include "globals.h"

uint16_t ticks = 0;
uint8_t readControl;
uint8_t menuOption = 0;

#define MAX_OPTIONS_MENU 6
#define MAX_LENGHT_MENU 24
#define NUM_MENU_OPTIONS 3 //TODO: Keep Updated

const char menu[MAX_OPTIONS_MENU][MAX_LENGHT_MENU] = {
														"Play",
														"Options",
														"Help"
	
};

void printMenu(uint8_t menuOption){
	uint8_t c;
	for ( c= 0; c < NUM_MENU_OPTIONS; c++) {
		gotoCharOLED(c,0);
		if (c == menuOption) putInvertedSOLED(menu[c]);
		else putsOLED(menu[c]);
	}
}

void initExtMemIface(){
	MCUCR |= (1 << SRE);
}

void initTimer(){ //It will raise a timer interrupt every aprox 10th of sec.
	//TCCR1B = 0b00000101; //Set source and prescaler
	TCCR1B |= (1 << CS11);
	TIMSK  |= (1 << TOIE1); //Enable interrupt by overlfow
}

void stopTimer(){
	TCCR1B &= ~(1 << CS11);
	
}




ISR(INT0_vect) //Interrupt routine for the ADC
{
	resultADC = *extADC;
	flagADC = 1;
}	

ISR(INT1_vect) //Interrupt routine for the Int1 (Joystick Button)
{
	flagJoyButton = 1;
}

ISR(TIMER1_OVF_vect)
{
	ticks++;
	if( ticks >= 5 ) {
			readControl = 1;
	}
}	
 

void initInterrupts(){
	DDRD  &= ~(1<<PD3); //Set INT1/PD3 as Input
	PORTD |= (1<<PD3); //Set pullup
	MCUCR |= 1<<ISC11; //Set interrupt on falling edge
	GICR |= (1<<INT1);
	GICR |= (1<<INT0); 
	sei();
}

void printHelp(){
	gotoCharOLED(0,0);
	putsOLED("Need help ?");
	gotoCharOLED(1,0);
	putsOLED("Try google ...");
	gotoCharOLED(2,0);
	putsOLED("or buy me beer");
	_delay_ms(5000);
	clearOLED();
}


int main(void)
{
	initUART(UBBR);
	printf("Simple RAM TEST \r\n");
	initExtMemIface();
	initTimer();
	initInterrupts();
	SRAM_test();
	joyInit();
	initOLED();
	initSPI();
    //setClockSpeedSPI();
	//while(1) writeSPI(0x55);
	/*while(1) {
		writeSPI(0xA0); //Read Status
		readSPI();
        //printf("SPI returns status Dec: %d Hex: %x \r\n", readSPI(), readSPI());
	}*/
	
	struct joypos_t c;
	enum joydir_t d;
	
	
	 while(1){
		if (readControl) {
			readControl = 0;
			d = getJoyDirection();
			if (d == TOP || d == RIGHT_TOP || d == LEFT_TOP) menuOption = (menuOption-1)%NUM_MENU_OPTIONS;
			else if (d == BOTTOM || d == RIGHT_BOTTOM|| d == LEFT_BOTTOM) menuOption = (menuOption+1)%NUM_MENU_OPTIONS;
			printMenu(menuOption);
		} if (flagJoyButton) {
		
			flagJoyButton = 0;
			gotoCharOLED(7,0);
			putsOLED("                        "); //Cleans last selected option from screen
			switch(menuOption){
				case 0: //Play
					gotoCharOLED(7,0);
					putsOLED("PLAY");
					break;
					
			   case 1: //Options
					gotoCharOLED(7,0);
					putsOLED("OPTIONS");
					break;
					
			   case 2: //Help
				    printHelp();
					break;
					
			  default:
					gotoCharOLED(7,0);
					putsOLED("Stick to the OPTIONS !!!");
					break;
				
			}
		}

//DO SOMETHING ELSE
		uint8_t resultSPI;        
 		/*printf("SPI TEST \r\n");
 		writeSPI(0xA0); //Read Status
		resultSPI = readSPI();*/
		 
		
		 
		//printf("SPI returns status Hex: %x \r\n",readCANCTL());
		/*for (resultSPI = 0; resultSPI < 3; resultSPI++){
			switch(resultSPI){
				case 0:
					writeSPI(0x00);
					break;
				case 1:
					writeSPI(0x55);
					break;
				case 2:
					writeSPI(0xFF);
					break;
			}
			
		}*/
		
		

		
		
	}
}