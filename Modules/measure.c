//******************************************************************************
//   
//	This module is used to give the distance kept by the IR sensor. It is composed
//	of a initialization function which call the initialization of the ADC module
//	and set the P1.1 pin where's the sensor is connected.
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

#include "msp430.h"
#include "ADC.h"

int memory;
int tab[10];
int value=0;
int i=0;

/*** Initialization ***/
void measure_init()
{
	ADC_init();
	P1SEL 	&=	~(BIT1);
	P1SEL2 	&=	~(BIT1);
	P1DIR 	&=	~(BIT1);
	P1OUT 	&=	~(BIT1);
}


/*** Take measures from the pin 1 - IR sensor ***/
int measure()
{
	value=0;
	for(i=0;i<10;i++)
	{

		ADC_Demarrer_conversion(1);
		tab[i]=ADC_Lire_resultat ();

	}

		do
		{

			for(i=0;i<10;i++)
			{
		        if(tab[i]>tab[i+1])
		        {
		           memory=tab[i];
		            tab[i]=tab[i+1];
		           tab[i+1]=memory;
		        }
			}

		}

		while(tab[0]>tab[1] || tab[1]>tab[2] || tab[2]>tab[3] || tab[3]>tab[4] || tab[4]>tab[5] || tab[5]>tab[6] || tab[6]>tab[7] || tab[7]>tab[8] || tab[8]>tab[9]);

		for(i=3;i<7;i++)
		{
		value=tab[i]+value;
		}

		value=value/4;

		return value;

}


