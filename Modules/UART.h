//------------------------------------------------------------------------------
// UART.h contains prototype of all managing functions for UART rotation
//------------------------------------------------------------------------------

#ifndef UART_H_
#define UART_H_

#include <msp430.h>

//------------------------------------------------------------------------------
// init_UART :  called to initialize the UART configuration
// IN:
// OUT:
// return:
//------------------------------------------------------------------------------
void init_UART(void);


//------------------------------------------------------------------------------
// TX_UART :  TX_UART is for send charactere in the buffer (UART fonction)
// IN:        c (unsigned char) character to send in the buffer.
// OUT:
// return:
//------------------------------------------------------------------------------
void TX_UART ( unsigned char c);


//------------------------------------------------------------------------------
// RX_UART :  RX_UART is for receive charactere from the buffer (UART fonction)
// IN:
// OUT:
// return:    UCA0RXBUF (unsigned char) buffer receive the character.
//------------------------------------------------------------------------------
unsigned char RX_UART (void);


#endif /* UART_H_ */
