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

ISR(INT2_vect) //Interrupt routine for the MCP2515 
{
	uint8_t mcp_flags;
	mcp_flags = readMCP(MCP_CANINTF);
	printf("Before Clearing: INTFs in MCP: %X \r\n", mcp_flags);
	
	writeMCP(MCP_CANINTF,0x00); //Clear Flags
	
	mcp_flags = readMCP(MCP_CANINTF);
	printf("After Clearing: INTFs in MCP: %X \r\n", mcp_flags);

	flagMCP = 1;
	
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
	EMCUCR &= ~(1<<ISC2); //Set interrupt on 0 at INT2
	GICR |= (1<<INT1);
	GICR |= (1<<INT0); 
	GICR |= (1<<INT2); 
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
	initCAN(NORMAL);
	
	struct joypos_t p;
	enum joydir_t d;
	struct canMessage m0,m1,m2s;

	 while(1){
		 
		/* slide1Point=getSlidePosition(1);
		 slide2Point=getSlidePosition(2);
		 printf("SLIDE1 -> %d",slide1Point.x);
		 printf("SLIDE2 -> %d",slide2Point.x);SLIDE READINGS*/
		if (readControl) {
			readControl = 0;
			
			d = getJoyDirection();
			p = getJoyPosition();
		    sendCANJoy(2,p,d);
			if (d == TOP || d == RIGHT_TOP || d == LEFT_TOP) menuOption = (menuOption-1)%NUM_MENU_OPTIONS;
			else if (d == BOTTOM || d == RIGHT_BOTTOM|| d == LEFT_BOTTOM) menuOption = (menuOption+1)%NUM_MENU_OPTIONS;
			printMenu(menuOption);
		}
		if (flagJoyButton) {
		
			m2s.id = JOY_BUTTON;
			m2s.size = 0;
			printf("Sending joy bu\r\n");
			fillTxBufferMCP(0,m2s);
			requestToSendMCP(0);
		
			struct canMessage m2s;
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
		/*
		if(flagMCP) {
			flagMCP = 0;
			struct canMessage m0,m1;
			m0 = readRxBufferMCP(0);
			m1 = readRxBufferMCP(1);
			printf ("Buffer 0 ID: %d, Size: %d, Data: %s \r\n", m0.id, m0.size, m0.data);
			printf ("Buffer 1 ID: %d, Size: %d, Data: %s \r\n", m1.id, m1.size, m1.data);
		}*/
	}
}