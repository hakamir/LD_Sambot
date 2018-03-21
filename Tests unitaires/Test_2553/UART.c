/******************************************************************************
 Name:                UART.c

 Description:         UART.c contains functions for UART utilisation




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

#include <msp430.h>
#include "UART.h"


/******************************************************************************
	UART_init :	called to initialize the UART configuration.
			input :	N/A
   	   	    output : N/A
******************************************************************************/
void UART_init(void)
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

/******************************************************************************
	UART_Tx :	UART_Tx sends character in the buffer (UART fonction).
			input :	c (unsigned char) character to send in the buffer.
   	   	    output : N/A
******************************************************************************/
void UART_Tx ( unsigned char c)
{
    while (!(IFG2 & UCA0TXIFG)); 	// USCI_A0 TX buffer ready?
    UCA0TXBUF = c; 				// TX -> RXed character
}


/******************************************************************************
	UART_Rx :	UART_Rx receives character from the buffer (UART fonction)
			input : N/A
   	   	    output :	UCA0RXBUF (unsigned char) buffer receive the character.
******************************************************************************/
unsigned char UART_Rx (void)
{
    while(!(UCA0RXIFG));
    return UCA0RXBUF;
}


/******************************************************************************
	envoi_msg_UART :	transmit an UART message
			input :	 tab of usigned char
   	   	    output : N/A.
******************************************************************************/
void envoi_msg_UART(unsigned char *msg)
{
    unsigned int i = 0;
    for(i=0 ; msg[i] != 0x00 ; i++)
    {
        UART_Tx(msg[i]);
    }
}
