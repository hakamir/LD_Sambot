/******************************************************************************

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

#include "msp430.h"
#include "measure.h"


/******************************************************************************
	measure_init :	This function initialize the port P1.1 where the IR sensor
	is connected and initialize the ADC.
			input :	N/A
   	   output :	N/A
******************************************************************************/
void measure_init(void)
{
    ADC_init();					/* Initialization of the ADC needed for the whole module */
    P1SEL 	&=	~(SENSOR);		
    P1SEL2 	&=	~(SENSOR);		
    P1DIR 	&=	~(SENSOR);		
    P1OUT 	&=	~(SENSOR);		/* The port of the sensor (BIT2) is ready to receive PWM value */
}


/******************************************************************************
 measure :	Take measures from the pin 0 - IR sensor
			input :	N/A
   	   output :	integer (between 0 and 1023)
******************************************************************************/
UINT32 measure(void)
{
    UINT32 memory;
    UINT32 tab[10];
    UINT32 value = 0;
    UINT32 i = 0;

    for(i=0;i<10;i++)
    {
        ADC_Demarrer_conversion(PIN_SENSOR);	/* The value coming from the sensor is converted by the ADC */

        tab[i] = ADC_Lire_resultat();			/* The digital value is stocked UINT32o a table */
    }

    do
    {
        for(i=0;i<10;i++)
        {
            if(tab[i]>tab[i+1])
            {
                memory = tab[i];
                tab[i] = tab[i+1];
                tab[i+1] = memory;
            }
        }
    }

    while((tab[0]>tab[1]) || (tab[1]>tab[2]) || (tab[2]>tab[3]) || (tab[3]>tab[4]) || (tab[4]>tab[5]) || (tab[5]>tab[6]) || (tab[6]>tab[7]) || (tab[7]>tab[8]) || (tab[8]>tab[9]));

    for(i=3;i<7;i++)
    {
        value = tab[i] + value;
    }

    value = (UINT32)(value/4);						/* All the previous code set a means of ten measures taken from the table  */

    return value;
}


/******************************************************************************
 convert_measure :	This function converts the value of function measure in
  meters. The value sends is between 40 and 300.
			input :	integer (between 0 and 1023)
   	   output :	integer (between 40 and 300)
******************************************************************************/
UINT32 convert_measure(UINT32 mes)
{
	const double a1 = -0.00000000000993030764967767;
	const double a2 = 0.000000214781420224059;
	const double a3 = -0.0000180638025675828;
	const double a4 = 0.007451829732734;
	const double a5 = -1.55467900656442;
	const double a6 = 145.552025091649;
    double mes_mm = a1*mes*mes*mes*mes*mes + a2*mes*mes*mes*mes + a3*mes*mes*mes + a4*mes*mes + a5*mes + a6;  /* Polynomial equation relative to the behaviour of the sensor */
    mes_mm = (UINT32) mes_mm;
    return mes_mm;
}

