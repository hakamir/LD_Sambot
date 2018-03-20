//------------------------------------------------------------------------------
// Name:                mainSlave.c
//
// Description:         mainSlave.c contains the slaves main
//
// Authors:             Marie DONNET & Rodolphe LATOUR
//
// Version:             1.0
//------------------------------------------------------------------------------

#include <msp430.h>
#include "servomotor.h"
#include "SPIS.h"

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    SPIS_init();
    servomotor_init();
    

    __bis_SR_register(LPM4_bits | GIE);
    while(1);
}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USI_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    unsigned char c = SPIS_Rx();
    switch (c)
    {
    case 0x30 :
        servomotor_set_deg(0);
        __delay_cycles(TIME_TO_CHECK);
        break;

    case 0x31 :
        servomotor_set_deg(45);
        __delay_cycles(TIME_TO_CHECK);
        break;

    case 0x32 :
        servomotor_set_deg(90);
        __delay_cycles(TIME_TO_CHECK);
        break;

    case 0x33 :
        servomotor_set_deg(135);
        __delay_cycles(TIME_TO_CHECK);
        break;
        
    case 0x34 :
        servomotor_set_deg(180);
        __delay_cycles(TIME_TO_CHECK);
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
