//******************************************************************************
// Name:                UART.h
//
// Description:         UART.h contains prototype of all managing functions for UART rotation
//
//
//
//
//                  	  		 	MSP430G2553
//                	   			 -----------------
//        	 	        	   -|VCC           GND|- 
//        	 	    IR Sensor ->|P1.0          XIN|-
//	 	  	   Data In (UART) ->|P1.1         XOUT|- 
//		 	  Data OUT (UART) <-|P1.2         TEST|- 
//      	        		  <-|P1.3          RST|--->
// Serial Clock Out (UCA0CLK) <-|P1.4         P1.7|-> Data Out (UCA0SIMO)
//  			  Slave reset <-|P1.5         P1.6|<- Data In (UCA0SOMI)
//		 		   odometer A ->|P2.0         P2.5|-> Sense Motor B
//	  		  	Sense Motor A <-|P2.1         P2.4|-> PWM Motor B
// 				  PWM Motor A <-|P2.2         P2.3|<- odometer B
//								 -----------------
//
//   Rodolphe LATOUR
//	 Marie DONNET
//   March 2018
//******************************************************************************

#ifndef UART_H_
#define UART_H_

#include <msp430.h>

//------------------------------------------------------------------------------
// UART_init :  called to initialize the UART configuration
// IN:
// OUT:
// return:
//------------------------------------------------------------------------------
void UART_init(void);


//------------------------------------------------------------------------------
// UART_Tx :  UART_Tx is for send charactere in the buffer (UART fonction)
// IN:        c (unsigned char) character to send in the buffer.
// OUT:
// return:
//------------------------------------------------------------------------------
void UART_Tx ( unsigned char c);


//------------------------------------------------------------------------------
// UART_Rx :  UART_Rx is for receive charactere from the buffer (UART fonction)
// IN:
// OUT:
// return:    UCA0RXBUF (unsigned char) buffer receive the character.
//------------------------------------------------------------------------------
unsigned char UART_Rx (void);


//------------------------------------------------------------------------------
// envoi_msg_UART :  transmit an UART message
// IN:
// OUT:
// return:
//------------------------------------------------------------------------------
void envoi_msg_UART(unsigned char *);

#endif /* UART_H_ */
