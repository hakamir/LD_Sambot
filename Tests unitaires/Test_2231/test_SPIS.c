/******************************************************************************
 Name:                test_SPIS.c

 Description:         permet de tester les fonctions du module SPIS.c

	Marie DONNET
	Rodolphe LATOUR
******************************************************************************/

#include <msp430.h> 
#include "SPIS.h"
/*
 * main.c
 */
void main(void) {

	WDTCTL = WDTPW | WDTHOLD;	/* Stop watchdog timer */
	
	/* Test fonction : SPIS_init() */
	SPIS_init();

	/* Test fonction : SPIS_Rx() */
	__bis_SR_register(LPM4_bits | GIE);


}


#pragma vector=USI_VECTOR
__interrupt void universal_serial_interface(void)
{
	unsigned char RXDta;
	RXDta = SPIS_Rx();

	if (RXDta == 0x31) /*if the input buffer is 0x31 (mainly to read the buffer)*/
	{
		P1OUT |= BIT0; /*turn on LED*/
	}
	else if (RXDta == 0x30)
	{
		P1OUT &= ~BIT0; /*turn off LED*/
	}
}
