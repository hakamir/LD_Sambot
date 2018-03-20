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
#define CS         BIT4            /* chip select for SPI Master->Slave ONLY on 4 wires Mode */
#define SCK         BIT5            /* Serial Clock */
#define DATA_OUT    BIT6            /* DATA out */
#define DATA_IN     BIT7            /* DATA in */

typedef unsigned char UCHAR;

//------------------------------------------------------------------------------
// SPIM_init : Initialization of SPI master
// IN:	 	none.
// OUT:    	none.
// return:  none.
//------------------------------------------------------------------------------


void SPIM_init(void)
{
    /* Waste Time, waiting Slave SYNC */
    __delay_cycles(250);

    /* SOFTWARE RESET - mode configuration */
    UCB0CTL0 = 0;
    UCB0CTL1 = (0 + UCSWRST*1 );

    /* clearing IFg /16.4.9/p447/SLAU144j
     set by setting UCSWRST just before */
    IFG2 &= ~(UCB0TXIFG | UCB0RXIFG);

    /* Configuration SPI (voir slau144 p.445)
     UCCKPH = 0 -> Data changed on leading clock edges and sampled on trailing edges.
     UCCKPL = 0 -> Clock inactive state is low.
       SPI Mode 0 :  UCCKPH * 1 | UCCKPL * 0
       SPI Mode 1 :  UCCKPH * 0 | UCCKPL * 0  <--
       SPI Mode 2 :  UCCKPH * 1 | UCCKPL * 1
       SPI Mode 3 :  UCCKPH * 0 | UCCKPL * 1
     UCMSB  = 1 -> MSB premier
     UC7BIT = 0 -> 8 bits, 1 -> 7 bits
     UCMST  = 0 -> CLK by Master, 1 -> CLK by USCI bit CLK / p441/16.3.6
     UCMODE_x  x=0 -> 3-pin SPI,
               x=1 -> 4-pin SPI UC0STE active high,
               x=2 -> 4-pin SPI UC0STE active low,
               x=3 -> i�c.
     UCSYNC = 1 -> Mode synchrone (SPI)*/
    UCB0CTL0 |= ( UCMST | UCMODE_0 | UCSYNC );
    UCB0CTL0 &= ~( UCCKPH | UCCKPL | UCMSB | UC7BIT );
    UCB0CTL1 |= UCSSEL_2;

    UCB0BR0 = 0x0A;     // divide SMCLK by 10
    UCB0BR1 = 0x00;

    /* SPI : Fonctions secondaires
     MISO-1.6 MOSI-1.7 et CLK-1.5
     Ref. SLAS735G p48,49 */
    P1SEL  |= ( SCK | DATA_OUT | DATA_IN);
    P1SEL2 |= ( SCK | DATA_OUT | DATA_IN);

    UCB0CTL1 &= ~UCSWRST;                                // activation USCI
}

//------------------------------------------------------------------------------
// SPIM_Tx :  master sends a char to slave
// IN:        char sent to slave (unsigned char).
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void SPIM_Tx(UCHAR c)
{
    while (!(IFG2 & UCB0TXIFG)); // USCI_B0 TX buffer ready?
    UCB0TXBUF = c;
}


//------------------------------------------------------------------------------
// SPIM_Rx : master receive a char to slave
// IN:	 	none.
// OUT:    	char sent to slave (unsigned char)
// return:  none.
//------------------------------------------------------------------------------
/*unsigned char SPIM_Rx(void)
{
    while(!(IFG2 & UCA0RXIFG));
    return UCA0RXBUF;
}*/

