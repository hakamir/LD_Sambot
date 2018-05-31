#include <msp430.h> 


/**
 * main.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

    //Ini Roues
    P2SEL |= (BIT4|BIT2);
    P2SEL2 &= ~(BIT4|BIT2);

    //Dir Pin Roues
    P2DIR |= (BIT5|BIT4|BIT2|BIT1);

    //Timer
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;

    //ini de la PWM
    TA1CTL = TASSEL_2 | MC_1;
    TA1CCTL1 |= OUTMOD_7;
    TA1CCTL2 |= OUTMOD_7;

    TA1CCR0=5000;

    TA1CCR1 = 0.2*TA1CCR0;      /*The value taken is assigned to the Left motor*/
    TA1CCR2 = 0.2*TA1CCR0;
    __delay_cycles(2000000);
    TA1CCR1 = TA1CCR0;      /*The value taken is assigned to the Left motor*/
    TA1CCR2 = TA1CCR0;
    __delay_cycles(2000000);
    TA1CCR1 = 0;      /*The value taken is assigned to the Left motor*/
    TA1CCR2 = 0;
    __delay_cycles(2000000);
    TA1CCR1 = 0.5*TA1CCR0;      /*The value taken is assigned to the Left motor*/
    TA1CCR2 = 0.5*TA1CCR0;
    __delay_cycles(2000000);
    P2OUT |= (BIT5);
    P2OUT |= (BIT1);
    TA1CCR1 = 0.2*TA1CCR0;      /*The value taken is assigned to the Left motor*/
    TA1CCR2 = 0.2*TA1CCR0;
    __delay_cycles(5000000);
    P2OUT &= ~(BIT5);
    P2OUT &= ~(BIT1);
    TA1CCR1 = 0.5*TA1CCR0;      /*The value taken is assigned to the Left motor*/
    TA1CCR2 = 0.5*TA1CCR0;
    __delay_cycles(5000000);
    P2OUT &= ~(BIT1);           /* Left motor go forward */
    P2OUT |= BIT5;



}
