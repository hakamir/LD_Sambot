/******************************************************************************
 Name:                mainMaster.c

 Description:         mainMaster.c contains the masters main

	Marie DONNET
	Rodolphe LATOUR
******************************************************************************/

#include <msp430.h>
#include "movement.h"
#include "UART.h"
#include "measure.h"
#include "SPIM.h"

#define TIME_TO_CHECK 300000

int mode = 0;   /* Mode manuel to start */

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; /*Stop watchdog timer*/

    /*Initialization of robot*/
    measure_init();
    init_timer_A1();
    move_init();
    SPIM_init();
    UART_init();

    /*Initialization of variables*/
    int mes;

    /* a char corresponds to a direction
     0x30 is to 0 deg
     0x31 is to 45 deg
     0x32 is to 90 deg
     0x33 is to 135 deg
     0x34 is to 180 deg*/
    unsigned char direction[8] = {0x30,0x31,0x32,0x33,0x34,0x33,0x32,0x31};

    stop();		/*Arrêt du robot*/

    __enable_interrupt();
    while(1)
    {
    	unsigned int i = 0;
    	for (i=0;i<8;i++)		/* sweeping of servomotor*/
    	{
    		SPIM_Tx(direction[i]);
    		__delay_cycles(TIME_TO_CHECK);
    		mes = measure();		/* measure with sensor IR*/
    		if (mode == 1)			/* auto mode */
    		{
    			automode(mes,direction[i]);
    		}
    		else if (mode == 0)		/* manual mode */
    		{
    			if (mes > 300)
    			{
    				envoi_msg_UART("\r\nEvitez l'objet !");		/* obstacle forward robot */
    			}
    		}
    	}
    }
}

/* Echo back RXed character, confirm TX buffer is ready first*/
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    unsigned char c = UART_Rx();
    switch (c)
    {
    case '8' :
        move(FORWARD,speed,speed);			/* robot go forward */
        envoi_msg_UART("\r\nLe robot avance");
        mode = 0; /* manual mode */
        break;

    case '2' :
        move(BACKWARD,speed,speed);			/* robot go backward */
        envoi_msg_UART("\r\nLe robot recule");
        mode = 0; /* manual mode */
        break;

    case '4' :
        move(LEFT,100,100);				/* Turn 45 deg left */
        __delay_cycles(TIME_TO_TURN);
        move(FORWARD,speed,speed);			/* robot go forward */
        envoi_msg_UART("\r\nLe robot tourne a gauche a 45 degres");
        mode = 0; /* manual mode */
        break;

    case '6' :
        move(RIGHT,100,100);			/* Turn 45 deg right */
        __delay_cycles(TIME_TO_TURN);
        move(FORWARD,speed,speed);			/* robot go forward */
        envoi_msg_UART("\r\nLe robot tourne a droite a 45 degres");
        mode = 0; /* manual mode */
        break;

    case '5' :
        stop();							/* robot stop */
        envoi_msg_UART("\r\nLe robot s'arrete");
        mode = 0; /* manual mode */
        break;

    case '1' :
        mode = 1; /* automatic mode */
        envoi_msg_UART("\r\nMode automatique");
        break;

    case '0' :
        mode = 0; /* manual mode */
        envoi_msg_UART("\r\nMode manuel");
        break;

    case 'z'
        mode = 0; /* manual mode */
        speed = 20
        envoi_msg_UART("\r\nVitesse a 20%");
        break;

    case 'u'
        mode = 0; /* manual mode */
        speed = 40;
        envoi_msg_UART("\r\nVitesse a 40%");
        break;

    case 'd'
        mode = 0; /* manual mode */
        speed = 60;
        envoi_msg_UART("\r\nVitesse a 60%");
        break;

    case 't'
        mode = 0; /* manual mode */
        speed = 80;
        envoi_msg_UART("\r\nVitesse a 80%");
        break;

    case 'q'
        mode = 0; /* manual mode */
        speed = 100;
        envoi_msg_UART("\r\nVitesse a 100%");
        break;

    case 'h' :
        envoi_msg_UART("\r\nh : Aide");
		envoi_msg_UART("\r\n8 : Faire avancer le robot");
		envoi_msg_UART("\r\n2 : Faire reculer le robot");
		envoi_msg_UART("\r\n4 : Faire tourner le robot a gauche");
		envoi_msg_UART("\r\n6 : Faire tourner le robot a droite");
		envoi_msg_UART("\r\n5 : Arreter le robot");
		envoi_msg_UART("\r\n0 : Robot en mode manuel");
		envoi_msg_UART("\r\n1 : Robot en mode automatique");
        break;
    }
}
