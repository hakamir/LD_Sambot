/******************************************************************************
 SPIM.h
******************************************************************************/

#ifndef SPI_Saster_H_
#define SPI_Saster_H_

#include <msp430.h>


/******************************************************************************
	SPIM_init :	Initialization of SPIM.
			input :	N/A
   	   	    output : N/A
******************************************************************************/
void SPIM_init(void);


/******************************************************************************
	SPIM_Tx :	master sends a char to slave.
			input :	char sent to slave (unsigned char)
   	   	    output : N/A
******************************************************************************/
void SPIM_Tx(unsigned char);


#endif /* SPI_Saster_H_ */
