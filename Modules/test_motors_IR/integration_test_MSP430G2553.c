#include <msp430.h> 
#include "measure.h"
#include "movement.h"
#include "UART.h"
#include "servomotor.h"



#define DEG_90 300000
#define DEG_180 600000
#define TIME_1 1000000
#define TIME_2 5000000


int a;
int distance;
char c;
int mode;

/* --------------------------------------------------------------------------------------- */

void auto_behaviour(int mode) {
	switch(mode)
	{
	case 1 :
	    move(FORWARD, 100, 100);
	    __delay_cycles(TIME_2);

	    stop();
	    __delay_cycles(TIME_1);

	    move(RIGHT, 80, 80);
	    __delay_cycles(DEG_90*2);

	    stop();
	    __delay_cycles(TIME_1);

	    move(FORWARD, 100, 100);
	    __delay_cycles(TIME_2);

	    break;
	case 2 :
	    move(FORWARD, 100, 100);
	    __delay_cycles(TIME_2);
	    __delay_cycles(TIME_1);

	    stop();
	    __delay_cycles(TIME_2);

	    move(LEFT, 80, 80);
	    __delay_cycles(DEG_180);

	    move(FORWARD, 100, 100);
	    __delay_cycles(TIME_2);
	    break;
	}
}


/* --------------------------------------------------------------------------------------- */

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    /*** Initializations ***/
    init_timer_A1();
    UART_init();
	measure_init();
	move_init();
	servomotor_init();

	stop();			/* Stop the robot */
	__enable_interrupt();
    while(1)
    {

    	c = UART_Rx();
    	if (mode == 1)
		{
			auto_behaviour(1);
		}
    	else if (mode == 2)
		{
			auto_behaviour(2);
		}
    }
}


/* --------------------------------------------------------------------------------------- */

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	c = UART_Rx();
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
	case '9' :
		mode = 1;
		break;
	case '7' :
		mode = 2;
		break;
	case '0' :
		mode = 0;
		break;
	}
}


