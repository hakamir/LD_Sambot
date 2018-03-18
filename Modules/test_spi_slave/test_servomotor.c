#include <msp430.h> 
#include "servomotor.h"
/*
 * main.c
 */
void main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    // Test fonction : servomotor_init()
    servomotor_init();

    // Test fonction : servomotor_PWM_init()
    servomotor_PWM_init();

    // Test fonction : servomotor_stop()
    /*__enable_interrupt();
    while(1)
        {
        	servomotor_sweeping();
        }
    */

    // Test fonction : servomotor_set_deg ()
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

    // Test fonction : servomotor_sweeping()
    /*while(1)
    {
    	servomotor_sweeping();
    }*/

}
