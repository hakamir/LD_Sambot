//------------------------------------------------------------------------------
// SPIS_Tx.h 
//------------------------------------------------------------------------------

#ifndef SPI_Slave_H_
#define SPI_Slave_H_

#include <msp430.h>

//------------------------------------------------------------------------------
// SPIS_Tx : slave sends a char to master
// IN:	 	char sent to master (unsigned char)
// OUT:    	none.
// return:  none.
//------------------------------------------------------------------------------
void SPIS_Tx(unsigned char);


#endif /* SPI_Slave_H_ */
