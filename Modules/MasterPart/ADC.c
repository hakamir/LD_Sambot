
#include "msp430.h"
#include "ADC.h"


/******************************************************************************
	ADC_init :	This function initialize the ADC.
			input :	N/A
   	   	    output : N/A
******************************************************************************/
void ADC_init(void)
{
	ADC10CTL0 = ADC10CTL1 = 0;

// Choix de la r�f�rence de tension Vcc GND
// R�f�rence interne active et g�n�rateur � 2,5 Volts  ADC10 actif
// Les autres bits sont suppos�s � 0 

	ADC10CTL0 =  SREF_0 + ADC10SHT_0  + REF2_5V + REFON + ADC10ON;  ;  

// Choix du diviseur par 1 pour l'horloge, d�marrage conversion logiciel
// Horloge de conversion 1MHz, conversion monovoie-monocoup	

	ADC10CTL1 =  ADC10DIV_0 + ADC10SSEL_2 +  SHS_0 + CONSEQ_0 ;
}

/******************************************************************************
	ADC_Demarrer_conversion :	This function converts a tension of a number.
			input :	unsigned char (port where sensor IR is connected)
 	   	    output : N/A
******************************************************************************/
void ADC_Demarrer_conversion(unsigned char voie)
{
    ADC10CTL1 = (voie * 0x1000)+ ADC10DIV_0 + ADC10SSEL_2 +  SHS_0 + CONSEQ_0 ;
    ADC10CTL0 |= ENC + ADC10SC;     // Sampling and conversion start
 }  

/******************************************************************************
	ADC_Lire_resultat :	This function return a number which corresponds to a distance.
			input :	N/A
   	   	    output : integer (between 0 and 1023)
******************************************************************************/
int ADC_Lire_resultat ()
{
  	while (ADC10CTL1 & ADC10BUSY);	// Tant que ADC occup� on attend
	ADC10CTL0 &= ~ENC;		// Conversion finie alors Disable ADC conversion
    	return ADC10MEM;	        // Return Conversion value
}
