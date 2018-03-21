/******************************************************************************
	ADC.h
******************************************************************************/

#ifndef ADC_H_
#define ADC_H_


/******************************************************************************
	ADC_init :	This function initialize the ADC.
			input :	N/A
   	   	    output : N/A
******************************************************************************/
void ADC_init(void);


/******************************************************************************
	ADC_Demarrer_conversion :	This function converts a tension of a number.
			input :	unsigned char (port where sensor IR is connected)
 	   	    output : N/A
******************************************************************************/
void ADC_Demarrer_conversion(unsigned char voie);
 

/******************************************************************************
	ADC_Lire_resultat :	This function return a number which corresponds to a distance.
			input :	N/A
   	   	    output : integer (between 0 and 1023)
******************************************************************************/
int ADC_Lire_resultat ();

#endif /* ADC_H_ */
