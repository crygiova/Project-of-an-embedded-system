/*
 * globals.h
 *
 * Created: 31.08.2012 14:35:11
 *  Author: jordifr
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_


#define F_CPU 4915200UL
//#define F_CPU 2000000UL
#define BAUD 9600
#define UBBR 31



#include <avr/io.h>
#include "util/delay.h"
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#include "adc.h"
#include "joy.h"
#include "uart.h"
#include "oled.h"
#include "spi.h"
#include "can.h"

/**Porta of high addresses*/
#define ADDRESS_LOW PORTA
/**Portc of high addresses*/
#define ADDRESS_HIGH PORTC

// structure to allow bit field operations, name conversions: PORTA.0 -> PORT_A.b0  PORTB.7 -> PORT_B.b7
typedef struct{ uint8_t b0:1;
                uint8_t b1:1;
                uint8_t b2:1;
                uint8_t b3:1;
                uint8_t b4:1;
                uint8_t b5:1;
                uint8_t b6:1;
                uint8_t b7:1; } bits;

#define PORT_E (* (volatile bits *) &PORTE)
#define PORT_B (* (volatile bits *) &PORTB)
/**Latch enable signal*/
#define ALE PORT_E.b1;

extern volatile char* extADC; //Adress to access ADC on XMEM
extern volatile uint8_t flagJoyButton; //Flag to indicate joybutton is pressed
extern volatile uint8_t flagMCP; //Flag to indicate joybutton is pressed
extern volatile char* extDataOled; //Adress for the Data reg of the OLED
extern volatile char* extCommandOled; //Adress for the Command reg of the OLED


/**macros for bit level operations */
/*#define set_bit( reg, bit ) (reg |= (1 << bit))
#define clear_bit( reg, bit ) (reg &= ~(1 << bit))
#define test_bit( reg, bit ) (reg & (1 << bit))
#define loop_until_bit_is_set( reg, bit ) while( !test_bit( reg, bit ) )
#define loop_until_bit_is_clear( reg, bit ) while( test_bit( reg, bit ) )
*/

#endif /* GLOBALS_H_ */