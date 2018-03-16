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
void SPIS_init(void)
{
	P1OUT =  BIT4;                        // P1.4 set, else reset
	P1REN |= BIT4;                        // P1.4 pullup
	P1DIR = BIT0;                         // P1.0 output, else input
	
	// USI Config. for SPI 3 wires Slave Op.
    // P1SEL Ref. p41,42 SLAS694J used by USIPEx
    USICTL0 |= USISWRST;
    USICTL1 = 0;		           
	
	// 3 wire, mode Clk&Ph / 14.2.3 p400
    // SDI-SDO-SCLK - LSB First - Output Enable - Transp. Latch
    USICTL0 |= (USIPE7 | USIPE6 | USIPE5 | USILSB | USIOE | USIGE );
    // Slave Mode SLAU144J 14.2.3.2 p400
    USICTL0 &= ~(USIMST);
    USICTL1 |= USIIE;
    USICTL1 &= ~(USICKPH | USII2C);

    USICKCTL = 0; 			// No Clk Src in slave mode
    USICKCTL &= ~(USICKPL | USISWCLK);	// Polarity - Input ClkLow

    USICNT = 0;
    USICNT &= ~(USI16B | USIIFGCC ); // Only lower 8 bits used 14.2.3.3 p 401 slau144j
    USISRL = 0x23;					// hash, just mean ready; USISRL Vs USIR by ~USI16B set to 0
    USICNT = 0x08;
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
