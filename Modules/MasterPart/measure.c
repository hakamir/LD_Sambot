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
#include <math.h>


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
    /*double mes_mm = 16184 * pow(mes,-0.692);*/  /* Formula finds with several measures /!\ DOES WORK WITH THE MSP430, A POLYNOMIAL REGRESSION HAVE TO BE FOUND /!\ */
    /*mes_mm = (UINT32) mes_mm;
    return mes_mm;*/
	return 0;
}

