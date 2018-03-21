/******************************************************************************
 Name:                test_servomotor.c

 Description:         permet de tester les fonctions du module servomotor.c

	Marie DONNET
	Rodolphe LATOUR
******************************************************************************/

#include <msp430.h> 
#include "servomotor.h"
/*
 * main.c
 */
void main(void) {

	WDTCTL = WDTPW | WDTHOLD;	/* Stop watchdog timer */

	/* Initialisation P1.3 (bouton) pour le test de la fonction servomotor_stop() */
	P1DIR &=~ (BIT3);
	P1IES |= (BIT3);
	P1IFG &= ~(BIT3);
	P1IE |= (BIT3);
	
	/* Test fonction : servomotor_init() */
	servomotor_init();

	/* Test fonction : servomotor_PWM_init() */
	servomotor_PWM_init();

	/* Test fonction : servomotor_set_deg () */
	TACCR1 = servomotor_set_deg(0);
	__delay_cycles(1200000);
	TACCR1 = servomotor_set_deg(45);
	__delay_cycles(1200000);
	TACCR1 = servomotor_set_deg(135);
	__delay_cycles(1200000);
	TACCR1 = servomotor_set_deg(90);
	__delay_cycles(1200000);
	TACCR1 = servomotor_set_deg(180);
	__delay_cycles(1200000);
	TACCR1 = servomotor_set_deg(53);
	__delay_cycles(1200000);
	TACCR1 = servomotor_set_deg(0);
	__delay_cycles(1200000);



	/* Test fonction : servomotor_stop() */
	__enable_interrupt();
	while(1)
	{
		TACCR1 = servomotor_set_deg(0);
		__delay_cycles(300000);
		TACCR1 = servomotor_set_deg(45);
		__delay_cycles(300000);
		TACCR1 = servomotor_set_deg(90);
		__delay_cycles(300000);
		TACCR1 = servomotor_set_deg(135);
		__delay_cycles(300000);
		TACCR1 = servomotor_set_deg(180);
		__delay_cycles(300000);
		TACCR1 = servomotor_set_deg(135);
		__delay_cycles(300000);
		TACCR1 = servomotor_set_deg(90);
		__delay_cycles(300000);
		TACCR1 = servomotor_set_deg(45);
		__delay_cycles(300000);
	}

}
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	while( !(P1IN & BIT3) );
	servomotor_stop();
}
