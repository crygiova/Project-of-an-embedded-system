/*
 * Node2.c
 *
 * Created: 12.10.2012 14:14:09
 *  Author: jordifr
 */ 

/*
 * Industrial.c
 *
 * Created: 10.09.2012 13:23:14
 *  Author: jordifr
 */ 

#include "globals.h"



ISR(ADC_vect){
	ADCReady = 1;
}


ISR(INT4_vect) //Interrupt routine for the CAN Transciver
{
	uint8_t mcp_flags;
	mcp_flags = readMCP(MCP_CANINTF);
	writeMCP(MCP_CANINTF,0x00); //Clear Flags
	
	//printf("CAN MCP General interrupt handler \r\n");
	
    if(mcp_flags & 1 << 0) {  //RX0IF
		//printf("CAN MCP Interrupt RX0IF Triggered \r\n");	
		flagMCP |= 	(1 << 0);
		
	}  if(mcp_flags & 1 << 1) { //RX1IF
		//printf("CAN MCP Interrupt RX1IF Triggered \r\n");
		flagMCP |= 	(1 << 1);
		
	}  if(mcp_flags & 1 << 2) { //TX0IF
		//printf("CAN MCP Interrupt TX0IF Triggered \r\n");
		flagMCP |= 	(1 << 2);
		
	}  if(mcp_flags & 1 << 3) { //TX1IF
	//	printf("CAN MCP Interrupt TX1IF Triggered \r\n");
		flagMCP |= 	(1 << 3);
		
	}  if(mcp_flags & 1 << 4) { //TX2IF
	//	printf("CAN MCP Interrupt TX2IF Triggered \r\n");
		flagMCP |= 	(1 << 4);
		
	}  if(mcp_flags & 1 << 5) { //ERRIF
	//	printf("CAN MCP Interrupt ERRIF Triggered  with error code 0x%x\r\n", readMCP(MCP_EFLG));
		
		
	}  if(mcp_flags & 1 << 6) { //WAKIF
	//	printf("CAN MCP Interrupt WAKIF\r\n");
		
		
	}  if(mcp_flags & 1 << 7) { //MERRF
	//	printf("CAN MCP Interrupt MERRF\r\n");
		
	} 

		


}	
 
void initInterrupts(){
 	DDRD  |= (1<<PD0) | (1 << PD1); //Set INT1/PD3 as Input
// 	PORTD |= (1<<PD3); //Set pullup
// 	MCUCR |= 1<<ISC11; //Set interrupt on falling edge
// 	EMCUCR &= ~(1<<ISC2); //Set interrupt on 0 at INT2
// 	GICR |= (1<<INT1);
// 	GICR |= (1<<INT0); 
// 	GICR |= (1<<INT2); 
//TODO: Configure to our interrupts
	DDRE &= ~(1<<PE4); //Set PE5 as Input
	DDRA |= (1 << PA7) | (1 << PA6) |(1 << PA5) | (1 << PA4) |(1 << PA3); //Set as output the needed pins in A
	DDRC = 0x00; //Make PORTC all inputs
	PORTC = 0x00;
	DDRF  |= (1<<PF2); //Set PF1 as output
	PORTF &= (~1 << PF1);
	PORTD |= (1<<PE4); //Set pullup for PE5
	EICRB |= (1<<ISC41);
	EICRB &= ~(1<<ISC40); //Set interrupts on falling edge at PE5
	EIMSK |= (1<<INT4); //Enable interrupt on PE5
	initADC();
	reload();
	sei();
}

uint8_t reverse(uint8_t byte){
	uint8_t i, reverse,temp;
	reverse = 0;
	for(i = 0; i < 8; i++){
		temp = ((byte & (1 << i)) << 7-i);
		reverse |= temp >> i;
	}
	return reverse;
}

// � Set !OE low to enable output of encoder
// � Set SEL low to get high byte
// � Wait about 20 microseconds
// � Read MSB
// � Set SEL high to get low byte
// � Wait about 20 microseconds
// � Read LSB
// � Toggle !RST to reset encoder
// � Set !OE high to disable output of encoder
// � Process received data....




void setEngineVoltageJoy(unsigned char axis){
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
}

int main(void)
{	
	struct canMessage m2s,rm;
	initUART(UBBR);
	TWI_Master_Initialise();
	initInterrupts();
	setReset();
	initMotor();
	
	PORTA |= (1 << PA4);
	printf("\r\n \r\n Hi, I am NODE 2 and this is NOT jackass, but we are getting there\r\n");

	
	initSPI();
	
	resetMCP();
	initCAN(NORMAL);	
	writeMCP(MCP_CANINTF, 0x01);
	char newCurrent = 0;
// 	    m2s.id = 42;
// 		m2s.size = 5;
// 		m2s.data[0] = 'H';
// 		m2s.data[1] = 'i';
// 		m2s.data[2] = ' ';
// 		m2s.data[3] = '2';
// 		m2s.data[4] = 0x00;
// 		
// 		fillTxBufferMCP(0,m2s);
// 		requestToSendMCP(0);

	
		initPWM();
		struct canMessage m0,m1, current;
	    int i = 0;
		
		 while(1){
		 if (i > 5) {
			printf("Read Encoder: %d \r\n", readEncoder());
			//_delay_ms(500);
			i = 0;
		 }
		 i++;		
		 
		//receiving
		if(flagMCP & 1 << 0) {
			flagMCP &= ~(1 << 0);
			m0 = readRxBufferMCP(0);
			current = m0;
			//printf ("Buffer 0 ID: %d, Size: %d, Data: %s \r\n", m0.id, m0.size, m0.data);
			newCurrent = 1;
		}
		
		else if(flagMCP & 1 << 1) {
			flagMCP &= ~(1 << 1);
			m1 = readRxBufferMCP(1);
			current = m1;
			//printf ("Buffer 1 ID: %d, Size: %d, Data: %s \r\n", m1.id, m1.size, m1.data);
			newCurrent = 1;
		}
		
		if(newCurrent) {
		
			switch (current.id){
				case JOY_MESSAGE:
				//	printf("Joystick X: %d    Y: %d   DIR: %d \r\n", current.data[0],current.data[1],current.data[2]);
					newCurrent = 0;
			//TODO decomment		setPWM(current.data[0]);
					setEngineVoltageJoy(current.data[1]);
				
					break;
					
					case JOY_BUTTON:
					shot();
					//printf("I am shooting \r\n");
					_delay_ms(150);
					reload();
					break;
					
					
				default:
					newCurrent = 0;
					//printf ("Current CAN message ID: %d, Size: %d, Data: %s \r\n", m1.id, m1.size, m1.data);
					//setPWM(current.data[0]);
					break;
			}
		}
		
		//Checking for GOAL
		volatile short temp = averageADC(10);
		if(temp < 10) {
		printf("GOAAAAALs: %d \r\n",score);		
		}
		
		
		
// 	    m2s.id = 24;
// 		m2s.size = 5;
// 		m2s.data[0] = 'B';
// 		m2s.data[1] = 'y';
// 		m2s.data[2] = ' ';
// 		m2s.data[3] = '3';
// 		m2s.data[4] = 0x00;
// 		
// 		fillTxBufferMCP(2,m2s);
// 		requestToSendMCP(2);
	
	
	
	}
	
}