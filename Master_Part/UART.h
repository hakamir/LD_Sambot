/******************************************************************************
 Name:                UART.h

 Description:         UART.h contains functions for UART utilisation




                  	  		 		MSP430G2553
                	   			 -----------------
        	 	        	   -|VCC           GND|-
        	 	    IR Sensor ->|P1.0          XIN|-
	 	  	   Data In (UART) ->|P1.1         XOUT|-
		 	  Data OUT (UART) <-|P1.2         TEST|-
        	        		  <-|P1.3          RST|--->
   Serial Clock Out (UCA0CLK) <-|P1.4         P1.7|-> Data Out (UCA0SIMO)
  	    		  Slave reset <-|P1.5         P1.6|<- Data In (UCA0SOMI)
		 		   odometer A ->|P2.0         P2.5|-> Sense Motor B
	  		  	Sense Motor A <-|P2.1         P2.4|-> PWM Motor B
 				  PWM Motor A <-|P2.2         P2.3|<- odometer B
								 -----------------

	Rodolphe LATOUR
	Marie DONNET
	March 2018
******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include <msp430.h>

/******************************************************************************
	UART_init :	called to initialize the UART configuration.
			input :	N/A
   	   	    output : N/A
******************************************************************************/
void UART_init(void);


/******************************************************************************
	UART_Tx :	UART_Tx sends character in the buffer (UART fonction).
			input :	c (unsigned char) character to send in the buffer.
   	   	    output : N/A
******************************************************************************/
void UART_Tx ( unsigned char c);


/******************************************************************************
	UART_Rx :	UART_Rx receives character from the buffer (UART fonction)
			input : N/A
   	   	    output :	UCA0RXBUF (unsigned char) buffer receive the character.
******************************************************************************/
unsigned char UART_Rx (void);


/******************************************************************************
	envoi_msg_UART :	transmit an UART message
			input :	 tab of usigned char
   	   	    output : N/A.
******************************************************************************/
void envoi_msg_UART(unsigned char *);

#endif /* UART_H_ */
