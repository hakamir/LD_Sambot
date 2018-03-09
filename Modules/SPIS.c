//------------------------------------------------------------------------------
// Name:                SPIS.c
//
// Description:         SPIS.c contains functions managing the servomotor
//
// Authors:             Marie DONNET & Rodolphe LATOUR
//
// Version:             1.0
//------------------------------------------------------------------------------

#include "SPIS.h"


//------------------------------------------------------------------------------
// SPIS_init : Initialization of init
// IN:	 	none.
// OUT:    	none.
// return:  none.
//------------------------------------------------------------------------------
void SPIS_init()
{
	WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
	P1OUT =  BIT4;                        // P1.4 set, else reset
	P1REN |= BIT4;                        // P1.4 pullup
	P1DIR = BIT0;                         // P1.0 output, else input
	USICTL0 |= USIPE7 + USIPE6 + USIPE5 + USIOE; // Port, SPI slave
	USICTL1 |= USIIE;           // Counter interrupt, flag remains set
	USICTL0 &= ~USISWRST;                 // USI released for operation
	USISRL = P1IN;                        // init-load data
	USICNT = 8;
}

//------------------------------------------------------------------------------
// SPIS_Tx :  slave sends a char to master
// IN:        char sent to master (unsigned char).
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void SPIS_Tx(unsigned char deg)
{
	USISRL = deg;
	USICNT = 8;
}


//------------------------------------------------------------------------------
// SPIS_Rx : slave receive a char to master
// IN:	 	none.
// OUT:    	char sent to master (unsigned char)
// return:  none.
//------------------------------------------------------------------------------
unsigned char SPIS_Rx(void)
{
	return USISRL;
}

/*// USI interrupt service routine
#pragma vector=USI_VECTOR
__interrupt void universal_serial_interface(void)
{
	switch(USISRL)
	{
	case '1' :
		servomotor_sweeping();
		break;

	case '3' :
		Servomotor_Stop();
		break;
	}
	USISRL = P1IN;
	USICNT = 8;                           // re-load counter
}
*/
