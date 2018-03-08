//------------------------------------------------------------------------------
// Name:                UART.c
//
// Description:         UART.c contains functions for UART utilisation
//
// Authors:             Marie DONNET & Rodolphe LATOUR
//
// Version:             1.0
//------------------------------------------------------------------------------

#include <msp430.h>
#include "UART.h"


//------------------------------------------------------------------------------
// init_UART :  called to initialize the UART configuration
// IN:
// OUT:
// return:
//------------------------------------------------------------------------------
void init_UART(void)
{
 P1SEL |= (BIT1 + BIT2); 					// P1.1 = RXD, P1.2=TXD
 P1SEL2 |= (BIT1 + BIT2); 					// P1.1 = RXD, P1.2=TXD
 UCA0CTL1 |= UCSSEL_2; 						// SMCLK
 UCA0BR0 = 104; 							// 1MHz, 9600
 UCA0BR1 = 0; 								// 1MHz, 9600
 UCA0CTL0 &= ~UCPEN & ~UCPAR & ~UCMSB;
 UCA0CTL0 &= ~UC7BIT & ~UCSPB & ~UCMODE1;
 UCA0CTL0 &= ~UCMODE0 & ~UCSYNC;
 UCA0CTL1 &= ~UCSWRST; 						// **Initialize USCI state machine**
 IE2 |= UCA0RXIE; 							// Enable USCI_A0 RX interrupt
}


//------------------------------------------------------------------------------
// TX_UART :  TX_UART is for send charactere in the buffer (UART fonction)
// IN:        c (unsigned char) character to send in the buffer.
// OUT:
// return:
//------------------------------------------------------------------------------
void TX_UART ( unsigned char c)
{
 while (!(IFG2&UCA0TXIFG)); 	// USCI_A0 TX buffer ready?
 UCA0TXBUF = c; 				// TX -> RXed character
}


//------------------------------------------------------------------------------
// RX_UART :  RX_UART is for receive charactere from the buffer (UART fonction)
// IN:
// OUT:
// return:    UCA0RXBUF (unsigned char) buffer receive the character.
//------------------------------------------------------------------------------
unsigned char RX_UART (void)
{
while(!(UCA0RXIFG));
return UCA0RXBUF;
}
