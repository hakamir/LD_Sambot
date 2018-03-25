//******************************************************************************
//	Name:                measure.h  
//
//	Description:         This module is used to give the distance kept by the IR sensor. It is composed
//						 of a initialization function 
//
//
//
//                  	  		 	MSP430G2553
//                	   			 -----------------
//        	 	        	   -|VCC           GND|- 
//        	 	    IR Sensor ->|P1.0          XIN|-
//	 	  	   Data In (UART) ->|P1.1         XOUT|- 
//		 	  Data OUT (UART) <-|P1.2         TEST|- 
//      	        		  <-|P1.3          RST|--->
// Serial Clock Out (UCA0CLK) <-|P1.4         P1.7|-> Data Out (UCA0SIMO)
//  			  Slave reset <-|P1.5         P1.6|<- Data In (UCA0SOMI)
//		 		   odometer A ->|P2.0         P2.5|-> Sense Motor B
//	  		  	Sense Motor A <-|P2.1         P2.4|-> PWM Motor B
// 				  PWM Motor A <-|P2.2         P2.3|<- odometer B
//								 -----------------
//
//   Rodolphe LATOUR
//	 Marie DONNET
//   March 2018
//******************************************************************************

#ifndef MEASURE_H_
#define MEASURE_H_

#include "ADC.h"

#define SENSOR BIT0
#define PIN_SENSOR 0

//******************************************************************************
//	measure_init :	This function initialize the port P1.1 where the IR sensor
//	is connected and initialize the ADC. 
//			input :	N/A
//   	   output :	N/A
//******************************************************************************
void measure_init(void);

//******************************************************************************
// measure :	This function take the distance give from the IR sensor
//	and send it in output. The value sends is between 0 and 1023.
//			input :	N/A
//   	   output :	integer (between 0 and 1023)
//******************************************************************************
int measure(void);

//******************************************************************************
// convert_measure :	This function converts the value of function measure in
//  meters. The value sends is between 40 and 300.
//			input :	integer (between 0 and 1023)
//   	   output :	integer (between 40 and 300)
//******************************************************************************
int convert_measure(int mes);

#endif /* MEASURE_H_ */
