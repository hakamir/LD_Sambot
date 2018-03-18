//------------------------------------------------------------------------------
// Name:                mainMaster.c
//
// Description:         mainMaster.c contains the masters main
//
// Authors:             Marie DONNET & Rodolphe LATOUR
//
// Version:             1.0
//------------------------------------------------------------------------------

#include <msp430.h>
#include "movement.h"
#include "UART.h"
#include "measure.h"
#include "SPIM.h"

#define TIME_TO_CHECK 300000

int mode = 0;   // Mode manuel au départ

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    measure_init();
    init_timer_A1();
    move_init();
    SPIM_init();
    UART_init();

    int mes;
    char direction[8] = {'0','1','2','3','4','3','2','1'};

    stop(); // Arrêt du robot

    __enable_interrupt();
    while(1)
    {
        if (mode == 1)
        {
            unsigned int i = 0;
            for(i=0;i<8;i++)
            {
                SPIM_Tx(direction[i]);
                __delay_cycles(TIME_TO_CHECK);
                mes = measure();
                automode(mes,direction[i]);
            }
        }
        else if (mode == 0)
        {
            unsigned int i = 0;
            for (i=0;i<8;i++)
            {
                SPIM_Tx(direction[i]);
                __delay_cycles(TIME_TO_CHECK);
                mes = measure();
                if (mes < 300)
                {
                    envoi_msg_UART("Evitez l'objet !");
                }
            }
        }

        /*move("FORWARD",80,80);
		dir = scan();
		move(dir,80,80);
		__delay_cycles(30000);
		move("FORWARD",80,80);*/
    }
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    unsigned char c = UART_Rx();
    switch (c)
    {
    case '8' :
        move(1,100,100);
        envoi_msg_UART("Le robot avance");
        mode = 0; // manuel mode
        break;

    case '2' :
        move(2,100,100);
        envoi_msg_UART("Le robot recule");
        mode = 0; // manuel mode
        break;

    case '4' :
        move(3,100,100);
        envoi_msg_UART("Le robot tourne a gauche");
        mode = 0; // manuel mode
        break;

    case '6' :
        move(4,100,100);
        envoi_msg_UART("Le robot tourne a droite");
        mode = 0; // manuel mode
        break;

    case '5' :
        stop();
        envoi_msg_UART("Le robot s'arrete");
        mode = 0; // manuel mode
        break;

    case '1' :
        mode = 1; // automatic mode
        envoi_msg_UART("Mode automatique");
        break;

    case '0' :
        mode = 0; // manuel mode
        envoi_msg_UART("Mode manuel");
        break;

    case 'h' :
        envoi_msg_UART("h : Aide");
        break;
    }
}


/*	char scan(void)
	{
		int mes[5];
		char dir;
		direction = SPIM_Rx();
		if (direction == '0')
		{
 *mes = scanc();
		}
		elseif(direction == '180')
		{
 *mes = scand();
		}

		int right = mes[0] + mes[1];
		int left =  mes[3] + mes[4]
								 int forward = mes[2]*2;

		if (right > left && right > forward)
			dir = 'RIGHT';
		else if (left > right && left > forward)
			dir = 'LEFT';
		else
			dir = 'FORWARD';

		return(dir);
	}

	int *scanc(void)
	{
		int mes[5];
		mes[0] = measure();
		for (i=1,i<5,i++)
		{
			direction = SPIM_Rx();
			mes[i] = measure();
		}
		return *mes;
	}

	int *scand(void)
	{
		int mes[5];
		mes[5] = measure();
		for (i=4,i>=0,i--)
		{
			direction = SPIM_Rx();
			mes[i] = measure();
		}
		return *mes;
	}*/
