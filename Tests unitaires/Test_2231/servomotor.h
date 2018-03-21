/******************************************************************************
 Name:                servomotor.h

 Description:         servomotor.h contains prototype of all managing functions for servomotor rotation




                  	  		 		MSP430G2231
                	   			 -----------------
        	 	        	   -|VCC           GND|-
        	 	        	   -|P1.0          XIN|-
	 	  	   				   -|P1.1         XOUT|-
		 	  		Stepmotor <-|P1.2         TEST|-
      	       			  	  <-|P1.3          RST|--->
   Serial Clock Out (UCA0CLK) <-|P1.4         P1.7|-> Data Out (UCA0SIMO)
  			  	  Slave reset ->|P1.5         P1.6|<- Data In (UCA0SOMI)
								 -----------------


	Rodolphe LATOUR
	Marie DONNET
	March 2018
******************************************************************************/

#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include <msp430.h>

#define SERVOMOTOR BIT2
#define SERVOMOTOR_INIT 500
#define SERVOMOTOR_MAX 2500
#define TIME_TO_CHECK 300000

typedef int UINT32;

/******************************************************************************
	servomotor_init :	called to initialize the servomotor configuration
			input :	N/A
   	   	    output : N/A
******************************************************************************/
void servomotor_init(void);


/******************************************************************************
	servomotor_PWM_Init :	Called to start the pwm signal
			input :	N/A
   	   	    output : N/A
******************************************************************************/
void servomotor_PWM_init(void);


/******************************************************************************
	servomotor_stop :  stop the motor
			input :	N/A
   	   	    output : N/A
******************************************************************************/
void servomotor_stop(void);


/******************************************************************************
	servomotor_Set_Deg : realize the rotation to the degree in parameter
			input :	deg (UINT32) degree of rotation.
   	   	    output : UINT32 value of TACCR1 to set the rotation.
******************************************************************************/
UINT32 servomotor_set_deg(UINT32 deg);


#endif /* SERVOMOTOR_H_ */
