#include <msp430.h> 


/**
 * main.c
 */
#include "SPIS.h"
#include "servomotor.h"

int main(void)
{
    //P1DIR  = BIT4 ;
    P1DIR |= BIT0;
    P1OUT &=~BIT0;
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;      // Set DCO to 1Mhz
    DCOCTL = CALDCO_1MHZ;       // Set DCO to 1Mhz
    USICTL0 |= USISWRST;
    SPIS_init();
    /* if(BIT4 & USISRL)
        {
            P1OUT |= BIT0;
        }
        else
        {
            P1OUT &= ~BIT0;
        }
          USISRL = P1IN;
          USICNT = 8;  */                        // re-load counter
    __enable_interrupt();
}

#pragma vector =USI_VECTOR
__interrupt void SPI_slave (void)
{
    unsigned char tamp ;
    tamp = SPIS_Rx();
    USICNT = 8;
    if ( 0x30 & tamp )
    {
        P1OUT |=BIT0;
    }
    else if ( 0x31 & tamp )
    {
        P1OUT &=~BIT0;
    }
}

/*void main(void)
{

   WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    servomotor_init();
    servomotor_start();
    P1DIR |= BIT0;
    P1OUT |= BIT0;

    //SPIS_init();



    //__bis_SR_register(LPM4 | GIE);
    while(1)
    {
        servomotor_sweeping();
    }
    //__enable_interrupt();


}
 */
/*#pragma vector = USI_VECTOR
__interrupt void universal_serial_interface(void)
{
    unsigned char a;
    a = SPIS_Rx();
    servomotor_set_deg(a);
    __delay_cycles(TIME_TO_CHECK*3);

}*/
