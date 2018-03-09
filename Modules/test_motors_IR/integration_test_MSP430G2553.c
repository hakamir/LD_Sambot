#include <msp430.h> 
#include "measure.h"
#include "movement.h"
#include "UART.h"
#include "servomotor.h"

/*
 * main.c
 */
int a;
int distance;
char c;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    /*** Initializations ***/
    init_timer_A1();
    init_UART();
	measure_init();
	init_move();
	Servomotor_Init();

	stop();			/* Stop the robot */

    while(1)
    {
    	__enable_interrupt();
    	c = RX_UART();
    }
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	switch (c)
	{
	case '8' :
		move(FORWARD, 100, 100);
		break;

	case '2' :
		move(BACKWARD,100,100);
		break;

	case '4' :
		move(LEFT, 100, 100);
		break;

	case '6' :
		move(RIGHT,100,100);
		break;

	case '1' :
		TACCR1 = Servomotor_Set_Deg(0);   // initialization to 0 deg
		__delay_cycles(TIME_TO_CHECK*4);
		TACCR1 = Servomotor_Set_Deg(0);   // set to 0 deg
		__delay_cycles(TIME_TO_CHECK);
		TACCR1 = Servomotor_Set_Deg(45);  // set to 45 deg
		__delay_cycles(TIME_TO_CHECK);
		TACCR1 = Servomotor_Set_Deg(90);  // set to 90 deg
		__delay_cycles(TIME_TO_CHECK);
		TACCR1 = Servomotor_Set_Deg(135); // set to 135 deg
		__delay_cycles(TIME_TO_CHECK);
		TACCR1 = Servomotor_Set_Deg(180); // set to 180 deg
		__delay_cycles(TIME_TO_CHECK);
		TACCR1 = Servomotor_Set_Deg(135);  // set to 135 deg
		__delay_cycles(TIME_TO_CHECK);
		TACCR1 = Servomotor_Set_Deg(90);  // set to 90 deg
		__delay_cycles(TIME_TO_CHECK);
		TACCR1 = Servomotor_Set_Deg(45); // set to 45 deg
		__delay_cycles(TIME_TO_CHECK);
		break;

	case '3' :
		Servomotor_Stop();
		break;

	case '5' :
		stop();
		break;

	}
}
