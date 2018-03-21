/******************************************************************************
 Name:                test_UART.c

 Description:         permet de tester les fonctions du module UART.c

	Marie DONNET
	Rodolphe LATOUR
 ******************************************************************************/

#include <msp430.h> 
#include "UART.h"
/*
 * main.c
 */
void main(void) {

	WDTCTL = WDTPW | WDTHOLD;	/* Stop watchdog timer */
	P1DIR = BIT0;
	P1OUT &= ~BIT0;


	/* Test fonction : UART_init() */
	UART_init();

	/* Test fonction : UART_Tx() */
	UART_Tx('1');
	__delay_cycles(3000000);
	UART_Tx('5');
	__delay_cycles(3000000);
	UART_Tx('9');

	/* Test fonction : UART_Rx() */
	__enable_interrupt();

	/* Test fonction : envoi_msg_UART() */
	envoi_msg_UART("Bonjour");
	__delay_cycles(3000000);
	envoi_msg_UART("Test UART");

}


/* Echo back RXed character, confirm TX buffer is ready first*/
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	unsigned char c = UART_Rx();
	if (c == 0x31) /*if the input buffer is 0x31 (mainly to read the buffer)*/
	{
		P1OUT |= BIT0; /*turn on LED*/
	}
	else if (c == 0x30)
	{
		P1OUT &= ~BIT0; /*turn off LED*/
	}
}
