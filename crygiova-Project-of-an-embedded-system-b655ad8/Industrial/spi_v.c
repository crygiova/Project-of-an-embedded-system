//SPI interface
#include <avr/io.h>

void SPI_MasterInit(void)
{
	/* Set MOSI and SCK outp?t, all others input */
	DDRB |= (1<<DDB5)|(1<<DDB7)|(1<<DDB4);
	PORTB |= (1<<DDB4);
	/* Enable SPI, Master, s?t clock rate fck/16 */
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(char addr,char cData)
{
	/* Start transmission */
	PORTB &= ~(1<<DDB4);
	SPDR = 0x02;	//write instruction
	while(!(SPSR & (1<<SPIF)));
	SPDR = addr;//0x0F;	//address for control reg
	while(!(SPSR & (1<<SPIF)));
	SPDR = cData;
	/* Wait for transmission?complete */
	while(!(SPSR & (1<<SPIF)));
	PORTB = (1<<DDB4);
	;
}

void SPI_MasterRead(char addr)
{
	/* Start transmission */
	PORTB &= ~(1<<DDB4);
	SPDR = 0x03;	//write instruction
	while(!(SPSR & (1<<SPIF)));
	SPDR = addr;//0x0F;	//address for control reg
	while(!(SPSR & (1<<SPIF)));
	SPDR = 0x00;	//pushing out the data
	/* Wait for transmission?complete */
	while(!(SPSR & (1<<SPIF)));
	PORTB = (1<<DDB4);
	;
}



void SPI_RESET(void)
{
	/* Start transmission */
	PORTB &= ~(1<<DDB4);
	SPDR = 0xC0;	//reset instruction
	while(!(SPSR & (1<<SPIF)));
	PORTB = (1<<DDB4);
	;
}
void SPI_RXbufRead(char buf)
{
	/* Start transmission */
	PORTB &= ~(1<<DDB4);
	SPDR = buf;	//corresponding buffer read instruction
	while(!(SPSR & (1<<SPIF)));
	SPDR = 0x00;	//pushing data out
	while(!(SPSR & (1<<SPIF)));
	PORTB = (1<<DDB4);
	;
}

void SPI_LoadTXbuf(char buf, char data)
{
	/* Start transmission */
	PORTB &= ~(1<<DDB4);
	SPDR = buf;	//corresponding buffer load
	while(!(SPSR & (1<<SPIF)));
	SPDR = data;	//sending data to buffer
	while(!(SPSR & (1<<SPIF)));
	PORTB = (1<<DDB4);
	;
}

void SPI_RequestToSend(char buf)
{
	/* Start transmission */
	PORTB &= ~(1<<DDB4);
	SPDR = buf;	//corresponding buffer to send
	while(!(SPSR & (1<<SPIF)));
	PORTB = (1<<DDB4);
	;
}

