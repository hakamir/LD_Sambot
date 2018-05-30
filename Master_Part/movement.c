/******************************************************************************
	Name:                movement.c

	Description:         This module is used to set the direction and the speed that the robot SAMBot
 						 have to get. It is composed of two different functions that interact with the
						 pins of the MSP430G2xx3 affected to the manipulation


                  	  		 		MSP430G2553
                	   			 -----------------
        	 	        	   -|VCC           GND|-
        	 	    IR Sensor ->|P1.0          XIN|-
	 	  	   Data In (UART) ->|P1.1         XOUT|-
		 	  Data OUT (UART) <-|P1.2         TEST|-
      	        		  	  <-|P1.3          RST|--->
   Serial Clock Out (UCA0CLK) <-|P1.4         P1.7|-> Data Out (UCA0SIMO)
  			  	  Slave reset <-|P1.5         P1.6|<- Data In (UCA0SOMI)
		 		   odometer A ->|P2.0         P2.5|-> Sense Motor B
	  		  	Sense Motor A <-|P2.1         P2.4|-> PWM Motor B
 				  PWM Motor A <-|P2.2         P2.3|<- odometer B
								 -----------------

	Rodolphe LATOUR
	Marie DONNET
	March 2018
******************************************************************************/

#include <msp430.h>
#include "movement.h"



/******************************************************************************
	 	move_init :	This function initializes the ports of the device connected on
	the motherboard. (Odometers, motors and sense of rotation)
			input :	N/A
   	   	   output :	N/A
******************************************************************************/
void init_timer_A1(void)
{

    TA1CTL = TASSEL_2 | MC_1 | ID_0;	
    TA1CCTL1 = TA1CCTL2 = OUTMOD_7;		
    TA1CCR0 = 100;					/* Set to 100. The TA1CCR1 and TA1CCR2 can be a percentage of the TA1CCR0 */
    TA1CCR1 = 0;					/* Used to set the speed of the left motor */
    TA1CCR2 = 0;					/* Used to set the speed of the right motor */
}

//------------------------------------------------------------------------------
// move_init :  Initialization of each port
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------

void move_init(void)
{
    P2OUT &= ~(BIT1); 				/* Left motor go forward */
    P2OUT |= BIT5;					/* Right motor go forward */
    P2OUT &= ~BIT2;					/* Left motor is switched off */
    P2OUT &= ~BIT4;					/* Right motor is switched off */
    P2DIR |= (BIT1 | BIT2 | BIT4 | BIT5) ;
    P2DIR &= ~BIT0;
    P2DIR &= ~BIT3;
}


/******************************************************************************
	 		 move :	This function initializes the port P1.1 where the IR sensor
	is connected and initialize the ADC.
			input :	- enum int {FORWARD, BACKWARD, LEFT, RIGHT} -> direction of the robot
					- int -> speed of the left motor
					- int -> speed of the right motor
   	   	   output :	N/A
******************************************************************************/

void move(SINT_32 direction, SINT_32 speed_l, SINT_32 speed_r)
{


    /*direction =  {FORWARD, BACKWARD, LEFT, RIGHT};*/
    switch (direction)
    {
    case 1 :						/* Forward */
    {
        P2OUT |= (BIT2 | BIT4);		/* Both motors are switched on */
        P2OUT &= ~(BIT1); 			/* Left motor go forward */
        P2OUT |= BIT5;				/* Right motor go forward */
        break;
    }
    case 2 :						/* Backward */
    {
        P2OUT |= (BIT2 | BIT4);		/* Both motors are switched on */
        P2OUT |= BIT1;				/* Left motor go backward */
        P2OUT &= ~(BIT5);			/* Right motor go backward */
        break;
    }
    case 3 :						/* Left */
    {
        P2OUT |= (BIT2 | BIT4);		/* Both motors are switched on */
        P2OUT |= BIT1;				/* Left motor go backward */
        P2OUT |= BIT5;				/* Right motor go forward */
        break;
    }
    case 4 :						/* Right */
    {
        P2OUT |= (BIT2 | BIT4);		/* Both motors are switched on */
        P2OUT &= ~(BIT1);			/* Left motor go forward */
        P2OUT &= ~(BIT5);			/* Right motor go backward */
        break;
    }
    default :						/* Forward as default */
    {
        P2OUT |= (BIT2 | BIT4);		/* Both motors are switched on */
        P2OUT &= ~(BIT1); 			/* Left motor go forward */
        P2OUT |= BIT5;				/* Right motor go forward */
        break;
    }
    }


    /*** speed_l is a percentage of the TA1CCR0 set in the A1 timer function and act on the TA1CCR1 ***/
    /*** speed_r is a percentage of the TA1CCR0 set in the A1 timer function and act on the TA1CCR2 ***/
    if(((speed_l >= 0) && (speed_l <= 100)) && ((speed_r >= 0) && (speed_r <= 100)))	//The value taken have to be between 0% and 100%
    {
        TA1CCR1 = speed_l;		/*The value taken is assigned to the Left motor*/
        TA1CCR2 = speed_r;		/*The value taken is assigned to the Right motor*/
    }
    else
    {
        TA1CCR1 = 0;
        TA1CCR2 = 0;
    }
}


/******************************************************************************
	 		 stop :	This function stops both motors and do not change the sense of rotation
			input :	N/A
   	   	   output :	N/A
******************************************************************************/
void stop(void)
{
    P2OUT &= ~BIT2;					/* Left motor is switched off */
    P2OUT &= ~BIT4;					/* Right motor is switched off */
    return;
}


/******************************************************************************
	 	 automode :	function for automatic mode
			input :	- integer -> measure of sensor IR
					- unsigned char -> direction of sensor IR
   	   output :	N/A
******************************************************************************/
void automode(SINT_32 mes,unsigned char direction)
{
    int speed = 80;
    if (mes>300)
    {
        switch (direction)
        {
        case '0':   /* Object to left */
        {
            move(RIGHT,100,100);  /* Turn  45 deg right */
            __delay_cycles(TIME_TO_TURN);
            move(FORWARD,speed,speed);
            break;
        }
        case '1':  /* Object to left */
        {
            move(RIGHT,100,100);    /* Turn 90 deg right */
            __delay_cycles(TIME_TO_TURN*2);
            move(FORWARD,speed,speed);
            break;
        }
        case '2':      /* Object to forward */
        {
            move(RIGHT,100,100);        /* Turn 180 deg right */
            __delay_cycles(TIME_TO_TURN*4);
            move(FORWARD,speed,speed);
            break;
        }
        case '3':     /* Object to right */
        {
            move(LEFT,100,100);    /* Turn 90 deg left */
            __delay_cycles(TIME_TO_TURN*2);
            move(FORWARD,speed,speed);
            break;
        }
        case '4':     /* Object to right */
        {
            move(LEFT,100,100);    /* Turn 45 deg left */
            __delay_cycles(TIME_TO_TURN);
            move(FORWARD,speed,speed);
            break;
        }
        default :
        {
            break;
        }
        }
    }
    else
    {
    	move(FORWARD,100,100); 	/* Forward */
    }
}
