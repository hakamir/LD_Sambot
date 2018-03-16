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
#include "measure.h"
#include <math.h>


//------------------------------------------------------------------------------
// measure_init :  Called to initialized the IR sensor
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void measure_init(void)
{
    ADC_init();					/* Initialization of the ADC needed for the whole module */
    P1SEL 	&=	~(SENSOR);		
    P1SEL2 	&=	~(SENSOR);		
    P1DIR 	&=	~(SENSOR);		
    P1OUT 	&=	~(SENSOR);		/* The port of the sensor (BIT2) is ready to receive PWM value */
}


//------------------------------------------------------------------------------
// measure :  Take measures from the pin 0 - IR sensor
// IN:        none.
// OUT:       integer (between 0 and 1023).
// return:    none.
//------------------------------------------------------------------------------
int measure(void)
{
    int memory;
    int tab[10];
    int value = 0;
    int i = 0;

    for(i=0;i<10;i++)
    {
        ADC_Demarrer_conversion(PIN_SENSOR);

        tab[i] = ADC_Lire_resultat();
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

    while(tab[0]>tab[1] || tab[1]>tab[2] || tab[2]>tab[3] || tab[3]>tab[4] || tab[4]>tab[5] || tab[5]>tab[6] || tab[6]>tab[7] || tab[7]>tab[8] || tab[8]>tab[9]);

    for(i=3;i<7;i++)
    {
        value = tab[i] + value;
    }

    value = (int)(value/4);

    return value;
}

//------------------------------------------------------------------------------
// convert_measure :  converts the value of function measure in meters.
// IN:        			integer (between 0 and 1023).
// OUT:       			integer (between 40 and 300).
// return:    			none.
//------------------------------------------------------------------------------
int convert_measure(int mes)
{
    double mes_mm = 16184 * pow(mes,-0.692);  // formule find with several measures
    mes_mm = (int) mes_mm;
    return mes_mm;
}


//------------------------------------------------------------------------------
// scan_IR :  scan the espace forward robot. This is the automatic movement function. 
// IN:                  none.
// OUT:                 none.
// return:              none.
//------------------------------------------------------------------------------
void scan_IR(void)
{
    char direction_deg;
    int mes;

    direction_deg = SPIM_Rx();
    mes = measure();
    if (mes<300)
    {
        switch (direction_deg)
        {
        case '0':
        {
            move("RIGHT",80,80);
            __delay_cycles(15000);
            move("FORWARD",80,80);
            break;
        }
        case '45':
        {
            move('RIGHT',80,80);
            __delay_cycles(30000);
            move("FORWARD",80,80);
            break;
        }
        case '90':
        {
            move('RIGHT',80,80);
            __delay_cycles(60000);
            move("FORWARD",80,80);
            break;
        }
        case '135':
        {
            move('LEFT',80,80);
            __delay_cycles(30000);
            move("FORWARD",80,80);
            break;
        }
        case '180':
        {
            move("LEFT",80,80);
            __delay_cycles(15000);
            move("FORWARD",80,80);
            break;
        }
        default :
        {
            break;
        }
        }
    }
}
