/******************************************************************************
	Name:                measure.h
	This module is used to give the distance kept by the IR sensor. It is composed
	of a initialization function which call the initialization of the ADC module
	and set the P1.1 pin where's the sensor is connected.


                  	  		 		MSP430G2231
                	   			 -----------------
        	 	        	   -|VCC           GND|-
        	 	        	   -|P1.0          XIN|-
	 	  	   		IR Sensor <-|P1.1         XOUT|-
		 	  		Stepmotor <-|P1.2         TEST|-
        	       			  <-|P1.3          RST|--->
   Serial Clock Out (UCA0CLK) <-|P1.4         P1.7|-> Data Out (UCA0SIMO)
  			               	   -|P1.5         P1.6|<- Data In (UCA0SOMI)
								 -----------------


   Rodolphe LATOUR
   Marie DONNET
   March 2018
******************************************************************************/

#ifndef MEASURE_H_
#define MEASURE_H_

#include "ADC.h"

typedef int UINT32;
#define SENSOR BIT0
#define PIN_SENSOR 0


/******************************************************************************
	measure_init :	This function initialize the port P1.1 where the IR sensor
	is connected and initialize the ADC.
			input :	N/A
   	   output :	N/A
******************************************************************************/
void measure_init(void);


/******************************************************************************
 measure :	Take measures from the pin 0 - IR sensor
			input :	N/A
   	   output :	integer (between 0 and 1023)
******************************************************************************/
int measure(void);


/******************************************************************************
 convert_measure :	This function converts the value of function measure in
  meters. The value sends is between 40 and 300.
			input :	integer (between 0 and 1023)
   	   output :	integer (between 40 and 300)
******************************************************************************/
int convert_measure(int mes);


#endif /* MEASURE_H_ */
