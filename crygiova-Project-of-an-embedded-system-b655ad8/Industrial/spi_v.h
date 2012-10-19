#define CANCTRL 0x0F

#define LOOPBACK 0x30

#define RXBUFFER00 0x90
#define RXBUFFER01 0x91
#define RXBUFFER10 0x92
#define RXBUFFER11 0x93

#define TXBUFFER000 0x40
#define TXBUFFER001 0x41
#define TXBUFFER010 0x42
#define TXBUFFER011 0x43
#define TXBUFFER100 0x44
#define TXBUFFER101 0x45

void SPI_MasterInit(void);
void SPI_MasterTransmit(char addr,char cData);
void SPI_MasterRead(char addr);
void SPI_RESET(void);
void SPI_RXbufRead(char buf);
void SPI_LoadTXbuf(char buf, char data);
void SPI_RequestToSend(char buf);

