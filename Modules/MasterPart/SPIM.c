//------------------------------------------------------------------------------
// Name:                SPIS.c
//
// Description:         SPIM.c contains functions managing the SPI master
//
// Authors:             Marie DONNET & Rodolphe LATOUR
//
// Version:             1.0
//------------------------------------------------------------------------------

#include "SPIM.h"


//------------------------------------------------------------------------------
// SPIM_init : Initialization of SPI master
// IN:	 	none.
// OUT:    	none.
// return:  none.
//------------------------------------------------------------------------------
void SPIM_init(void)
{
	if(CALBC1_1MHZ==0xFF || CALDCO_1MHZ==0xFF)
	{
		__bis_SR_register(LPM4_bits);
	}
	else
	{
		BCSCTL1 = CALBC1_1MHZ;
		DCOCTL = CALDCO_1MHZ;
	}
	
	P1OUT |= BIT5;
	P1DIR |= BIT5;

	P1SEL |= (BIT1 + BIT2 + BIT4);
	P1SEL2 |= (BIT1 + BIT2 + BIT4);
	
	UCA0CTL1 = UCSWRST;
	
	UCA0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC; 
	UCA0CTL1 |= UCSSEL_2;  
	
	//UCABR0 = 0x02;
	//UCABR1 = 0x00;
	
	UCA0CTL1 = 0x00;
	
	P1OUT &= ~BIT5;
}

//------------------------------------------------------------------------------
// SPIM_Tx :  master sends a char to slave
// IN:        char sent to slave (unsigned char).
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void SPIM_Tx(unsigned char c)
{
	while(!(IFG2 & UCA0TXIFG));
	UCA0TXBUF = c;
}


//------------------------------------------------------------------------------
// SPIM_Rx : master receive a char to slave
// IN:	 	none.
// OUT:    	char sent to slave (unsigned char)
// return:  none.
//------------------------------------------------------------------------------
unsigned char SPIM_Rx(void)
{
	while(!(IFG2 & UCA0RXIFG));
	return UCA0RXBUF;
}

