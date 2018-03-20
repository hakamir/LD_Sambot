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
    if(CALBC1_1MHZ==0xFF || CALDCO_1MHZ==0xFF)
    {
        __bis_SR_register(LPM4_bits);
    }
    else
    {
        // Factory Set.
        DCOCTL = 0;
        BCSCTL1 = CALBC1_1MHZ;
        DCOCTL = (0 | CALDCO_1MHZ);
    }

    //--------------- Secure mode
    P1SEL = 0x00;        // GPIO
    P1DIR = 0x00;         // IN

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

    USICKCTL = 0;           // No Clk Src in slave mode
    USICKCTL &= ~(USICKPL | USISWCLK);  // Polarity - Input ClkLow

    USICNT = 0;
    USICNT &= ~(USI16B | USIIFGCC ); // Only lower 8 bits used 14.2.3.3 p 401 slau144j
    USISRL = 0x23;  // hash, just mean ready; USISRL Vs USIR by ~USI16B set to 0
    USICNT = 0x08;

    // Wait for the SPI clock to be idle (low).
    while ((P1IN & BIT5)) ;

    USICTL0 &= ~USISWRST;
}

//------------------------------------------------------------------------------
// SPIS_Tx :  slave sends a char to master
// IN:        char sent to master (unsigned char).
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
/*void SPIS_Tx(unsigned char deg)
{
	USISRL = deg;
	USICNT = 8;
}*/


//------------------------------------------------------------------------------
// SPIS_Rx : slave receive a char to master
// IN:	 	none.
// OUT:    	char sent to master (unsigned char)
// return:  none.
//------------------------------------------------------------------------------
unsigned char SPIS_Rx(void)
{
	while( !(USICTL1 & USIIFG) );   // waiting char by USI counter flag
	unsigned char c = USISRL;
    USICNT &= ~USI16B;  // re-load counter & ignore USISRH
    USICNT = 0x08;      // 8 bits count, that re-enable USI for next transfert
    return c;
}

