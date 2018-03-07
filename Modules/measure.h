//******************************************************************************
//   
//	This module is used to give the distance kept by the IR sensor. It is composed
//	of a initialization function 
//
//
//                  	  		 	MSP430G2231
//                	   			 -----------------
//        	 	        	   -|VCC           GND|- 
//        	 	        	   -|P1.0          XIN|-
//	 	  	   		IR Sensor <-|P1.1         XOUT|- 
//		 	  		Stepmotor <-|P1.2         TEST|- 
//      	       			  <-|P1.3          RST|--->
// Serial Clock Out (UCA0CLK) <-|P1.4         P1.7|-> Data Out (UCA0SIMO)
//  			  Slave reset <-|P1.5         P1.6|<- Data In (UCA0SOMI)
//								 -----------------
//
//
//   Rodolphe LATOUR
//   March 2018
//******************************************************************************

//******************************************************************************
//	 measure_init :	This function initialize the port P1.1 where the IR sensor
//	is connected and initialize the ADC. 
//			input :	N/A
//   	   output :	N/A
//******************************************************************************
void measure_init();

//******************************************************************************
//	 	  measure :	This function take the distance give from the IR sensor
//	and send it in output. The value sends is between 0 and 1023.
//			input :	N/A
//   	   output :	integer (between 0 and 1023)
//******************************************************************************
int measure();

