/******************************************************************************
 Name:                test_SPIM.c

 Description:         permet de tester les fonctions du module SPIM.c

	Marie DONNET
	Rodolphe LATOUR
 ******************************************************************************/

#include <msp430.h> 
#include "SPIM.h"
/*
 * main.c
 */
void main(void) {

	WDTCTL = WDTPW | WDTHOLD;	/* Stop watchdog timer */

	/* Test fonction : SPIM_init() */
	SPIM_init();

	/* Test fonction : SPIM_Tx() */
	while(1)
	{
		SPIM_Tx(0x30);
		__delay_cycles(3000000);
		SPIM_Tx(0x31);
		__delay_cycles(3000000);
	}
}
