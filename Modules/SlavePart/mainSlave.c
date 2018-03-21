
/******************************************************************************
 Name:                mainSlave.c

 Description:         mainSlave.c contains the slaves main

	Marie DONNET
	Rodolphe LATOUR
******************************************************************************/

#include <msp430.h>
#include "servomotor.h"
#include "SPIS.h"

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; /* Stop watchdog timer */

    /*Initialization of robot*/
    SPIS_init();
    servomotor_init();
    

    __bis_SR_register(LPM4_bits | GIE);
    while(1);
}

/* Echo back RXed character, confirm TX buffer is ready first*/
#pragma vector=USI_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    unsigned char c = SPIS_Rx();
    switch (c)
    {
    case 0x30 :
        servomotor_set_deg(0);			/*servomotor set to 0 deg*/
        __delay_cycles(TIME_TO_CHECK);
        break;

    case 0x31 :
        servomotor_set_deg(45);			/*servomotor set to 45 deg*/
        __delay_cycles(TIME_TO_CHECK);
        break;

    case 0x32 :
        servomotor_set_deg(90);			/*servomotor set to 90 deg*/
        __delay_cycles(TIME_TO_CHECK);
        break;

    case 0x33 :
        servomotor_set_deg(135);		/*servomotor set to 135 deg*/
        __delay_cycles(TIME_TO_CHECK);
        break;
        
    case 0x34 :
        servomotor_set_deg(180);		/*servomotor set to 180 deg*/
        __delay_cycles(TIME_TO_CHECK);
        break;
    }
}

