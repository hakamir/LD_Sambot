//------------------------------------------------------------------------------
// SPIM_Tx.h
//------------------------------------------------------------------------------

#ifndef SPI_Saster_H_
#define SPI_Saster_H_

#include <msp430.h>


//------------------------------------------------------------------------------
// SPIM_init : Initialization of init
// IN:	 	none.
// OUT:    	none.
// return:  none.
//------------------------------------------------------------------------------
void SPIM_init(void);

//------------------------------------------------------------------------------
// SPIM_Tx : master sends a char to slave
// IN:	 	char sent to slave (unsigned char)
// OUT:    	none.
// return:  none.
//------------------------------------------------------------------------------
void SPIM_Tx(unsigned char);


//------------------------------------------------------------------------------
// SPIM_Rx : master receive a char to slave
// IN:	 	none.
// OUT:    	char sent to slave (unsigned char)
// return:  none.
//------------------------------------------------------------------------------
unsigned char SPIM_Rx(void);


#endif /* SPI_Saster_H_ */
