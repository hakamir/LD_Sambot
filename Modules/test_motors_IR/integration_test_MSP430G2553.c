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
    UART_init();
	measure_init();
	move_init();
	servomotor_init();

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
		servomotor_sweeping();
		break;

	case '3' :
		servomotor_stop();
		break;

	case '5' :
		stop();
		break;

	}
}
