#include <msp430.h> 
#include "measure.h"
#include "movement.h"

/*
 * main.c
 */
int a;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    init_timer_A1();
	measure_init();
	init_move();
    while(1)
    {
    	a = measure();
    	move(FORWARD,80,80);
    	__delay_cycles(2000000);
    	move(FORWARD,20,80);
    	__delay_cycles(2000000);
    	move(BACKWARD,80,80);
    	__delay_cycles(2000000);
    	move(LEFT,40,40);
    	__delay_cycles(2000000);
    	move(RIGHT,20,20);
    	__delay_cycles(2000000);
    }
	return 0;
}
