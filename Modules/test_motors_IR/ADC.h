//******************************************************************************
// Name:                ADC.h
//
// Description:         ADC.h contains prototype of all managing functions for ADC manipulation
//
//
//	 ESIGELEC
//   March 2018
//******************************************************************************

//------------------------------------------------------------------------------
// ADC_init :  called to initialize the ADC configuration
// IN:
// OUT:
// return:
//------------------------------------------------------------------------------
void ADC_init(void);


//------------------------------------------------------------------------------
// ADC_convert :  ADC_convert is aimed to convert hexadecimal data into integer.
// IN:        voie (unsigned char) character to convert.
// OUT:
// return:
//------------------------------------------------------------------------------
void ADC_convert(unsigned char voie);
 

//------------------------------------------------------------------------------
// ADC_read :  ADC_read is used to give signal information coming from a specific pin.
// IN:        
// OUT:		   Give the integer value converted thanks to the ADC_convert function.
// return:
//------------------------------------------------------------------------------
int ADC_Lire_resultat ();
