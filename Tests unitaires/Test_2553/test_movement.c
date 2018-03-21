/******************************************************************************
 Name:                test_movement.c
 
 Description:         permet de tester les fonctions du module movement.c
 
 Marie DONNET
 Rodolphe LATOUR
 ******************************************************************************/

#include <msp430.h>
#include "movement.h"

/*
 * main.c
 */
void main(void) {
    
    WDTCTL = WDTPW | WDTHOLD;    /* Stop watchdog timer */
    P1DIR = BIT0;
    P1OUT &= ~BIT0;
    
    
    /* Test fonction : init_timer_A1() */
    init_timer_A1();
    
    /* Test fonction : move_init() */
    move_init();
    
    /* Test fonction : move() */
    move(FORWARD,20,80);
    __delay_cycles(3000000);
    move(BACKWARD,80,80);
    __delay_cycles(3000000);
    move(LEFT,40,40);
    __delay_cycles(3000000);
    move(RIGHT,20,20);
    __delay_cycles(3000000);
    move(10,120,-4);
    
    /* Test fonction : stop() */
    move(FORWARD,80,80);
    stop();
    
    /* Test fonction : automode() */
    automode(150,'0');
    automode(130,'1');
    automode(10,'2');
    automode(500,'0');
    automode(500,'1');
    automode(500,'2');
    automode(500,'3');
    automode(500,'4');
}
