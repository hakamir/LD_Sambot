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
    while(1)
    {
        servomotor_sweeping();
    }


   /* __delay_cycles(TIME_TO_CHECK);
    TACCR1 = 504;
    __delay_cycles(TIME_TO_CHECK);
        TACCR1 = 990;
    __delay_cycles(TIME_TO_CHECK);
    TACCR1 = 1476;
    __delay_cycles(TIME_TO_CHECK);
    TACCR1 = 1962;
    __delay_cycles(TIME_TO_CHECK);
    TACCR1 = 2448;

    __delay_cycles(TIME_TO_CHECK*4);
    TACCR1 = 504;

    __delay_cycles(TIME_TO_CHECK*4);
       TACCR1 = 1300;*/

    // Test fonction : servomotor_stop()
    //__enable_interrupt();
   // while(1)
       // {
     //   	servomotor_sweeping();
       // }


    // Test fonction : servomotor_set_deg ()
    /*TACCR1 = servomotor_set_deg(0);
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
    __delay_cycles(1200000);*/

    // Test fonction : servomotor_sweeping()
    /*while(1)
    {
    	servomotor_sweeping();
    }*/

}
