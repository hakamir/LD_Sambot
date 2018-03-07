
//******************************************************************************
//   
//	This module is used to set the direction and the speed that the robot SAMBot
// 	have to get. It is composed of two different functions that interact with the
//	pins of the MSP430G2xx3 affected to the manipulation
//
//
//                  	  		 	MSP430G2553
//                	   			 -----------------
//        	 	        	   -|VCC           GND|- 
//        	 	        	   -|P1.0          XIN|-
//	 	  	   Data In (UART) <-|P1.1         XOUT|- 
//		 	  Data OUT (UART) <-|P1.2         TEST|- 
//      	        		  <-|P1.3          RST|--->
// Serial Clock Out (UCA0CLK) <-|P1.4         P1.7|-> Data Out (UCA0SIMO)
//  			  Slave reset <-|P1.5         P1.6|<- Data In (UCA0SOMI)
//		 		   odometer A <-|P2.0         P2.5|-> Sense Motor B
//	  		  	Sense Motor A <-|P2.1         P2.4|-> PWM Motor B
// 				  PWM Motor A <-|P2.2         P2.3|-> odometer B
//								 -----------------
//
//   Rodolphe LATOUR
//   March 2018
//******************************************************************************

#include <msp430>


void move(enum direction {FORWARD, BACKWARD, LEFT, RIGHT}, int speed_l, int speed_r)
{
	
	/*** direction define the sense of rotation of each motor as well as the activation mode ***/
	
	switch direction
	{
		case FORWARD :
		{
			P2OUT |= (BIT2 | BIT4);		/* Both motors are switched on */
			P2OUT &= ~(BIT1); 			/* Left motor go forward */
			P2OUT |= BIT5;				/* Right motor go forward */
			break;
		}
		case BACKWARD :
		{
			P2OUT |= (BIT2 | BIT4);		/* Both motors are switched on */
			P2OUT |= BIT1;				/* Left motor go backward */
			P2OUT &= ~(BIT5);			/* Right motor go backward */
			break;
		}
		case LEFT :
		{
			P2OUT |= (BIT2 | BIT4);		/* Both motors are switched on */
			P2OUT |= BIT1;				/* Left motor go backward */
			P2OUT |= BIT5;				/* Right motor go forward */
			break;
		}
		case RIGHT :
		{
			P2OUT |= (BIT2 | BIT4);		/* Both motors are switched on */
			P2OUT &= ~(BIT1);			/* Left motor go forward */
			P2OUT &= ~(BIT5);			/* Right motor go backward */
			break;
		}
		default :
		{
			P2OUT |= (BIT2 | BIT4);		/* Both motors are switched on */
			P2OUT &= ~(BIT1); 			/* Left motor go forward */
			P2OUT |= BIT5;				/* Right motor go forward */
			break;
		}
	}
	
	
/*** speed_l is a percentage of the TA1CCR0 set in the A1 timer function and act on the TA1CCR1 ***/
	
	if((speed_l >= 0) && (speed_l <= 100))
	{
		double time_l = TA1CCR0*(speed_l/100);
		TA1CCR1 = (int)time_l;
	}
	else
	{
		TA1CCR1 = 0;
	}
	
	
/*** speed_r is a percentage of the TA1CCR0 set in the A1 timer function and act on the TA1CCR2 ***/
	
	if((speed_r >= 0) && (speed_r <= 100))
	{
		double time_r = TA1CCR0*(speed_r/100);
		TA1CCR2 = (int)time_r;
	}
	else
	{
		TA1CCR2 = 0;
	}
}

/*** stop is a function that define the activation mode of each motor to off without interact with the sense of rotation ***/

void stop()
{
	   P2OUT &= ~BIT2;					/* Left motor is switched off */
	   P2OUT &= ~BIT4;					/* Right motor is switched off */
	   return;
}