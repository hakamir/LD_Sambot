//******************************************************************************
// Name:                servomotor.h
//
// Description:         servomotor.h contains prototype of all managing functions for servomotor rotation
//
//
//
//
//                  	  		 	MSP430G2231
//                	   			 -----------------
//        	 	        	   -|VCC           GND|- 
//        	 	        	   -|P1.0          XIN|-
//	 	  	   				   -|P1.1         XOUT|- 
//		 	  		Stepmotor <-|P1.2         TEST|- 
//      	       			  <-|P1.3          RST|--->
// Serial Clock Out (UCA0CLK) <-|P1.4         P1.7|-> Data Out (UCA0SIMO)
//  			  Slave reset ->|P1.5         P1.6|<- Data In (UCA0SOMI)
//								 -----------------
//
//
//   Rodolphe LATOUR
//	 Marie DONNET
//   March 2018
//******************************************************************************

#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include <msp430.h>

#define SERVOMOTOR BIT2
#define SERVOMOTOR_INIT 500
#define SERVOMOTOR_MAX 2500
#define TIME_TO_CHECK 300000
//------------------------------------------------------------------------------
// Servomotor_Init :  called to initialize the ir motor configuration
// IN/OUT:    none.
// return:    none.
//------------------------------------------------------------------------------
void servomotor_init(void);

//------------------------------------------------------------------------------
// Servomotor_PWM_Init :  Called to start the pwm signal
// IN/OUT:    none.
// return:    none.
//------------------------------------------------------------------------------
void servomotor_PWM_init(void);

//------------------------------------------------------------------------------
// Servomotor_Stop :  stop the motor
// IN/OUT:    none.
// return:    none.
//------------------------------------------------------------------------------
void servomotor_stop(void);

//------------------------------------------------------------------------------
// Servomotor_Start :  start the motor
// IN/OUT:    deg (int) degree of rotation.
// return:    int value of TACCR1 to set the rotation.
//------------------------------------------------------------------------------
int servomotor_set_deg(int deg);

//------------------------------------------------------------------------------
// servomotor_sweeping :  realize the sweeping of IR sensor
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void servomotor_sweeping(void);
#endif /* SERVOMOTOR_H_ */
