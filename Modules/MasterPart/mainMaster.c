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
#include "measure.h"
#include "UART.h"


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    measure_init();
    init_timer_A1();
    init_move();
    SPIM_init();
    init_UART();

    while(1)
    {

        move("FORWARD",80,80);
        scan_IR();

        /*move("FORWARD",80,80);
		dir = scan();
		move(dir,80,80);
		__delay_cycles(30000);
		move("FORWARD",80,80);*/

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
