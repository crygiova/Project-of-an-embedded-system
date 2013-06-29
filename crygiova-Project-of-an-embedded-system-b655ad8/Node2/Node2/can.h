/*
 * can.h
 *
 * Created: 11.10.2012 16:51:24
 *  Author: chrisgio
 */ 


#ifndef CAN_H_
#define CAN_H_

#include "spi.h"



#define JOY_MESSAGE 10
#define JOY_BUTTON 11

#define CAN_TERMINATION 0x00


enum canMode {NORMAL, SLEEP, LOOPBACK, LISTEN, CONFIG};

void initCAN(enum canMode mode);

#endif /* CAN_H_ */