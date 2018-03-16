//------------------------------------------------------------------------------
// SPIS_Tx.h
//------------------------------------------------------------------------------

#ifndef SPI_Slave_H_
#define SPI_Slave_H_

#include <msp430.h>


//------------------------------------------------------------------------------
// SPIS_init : Initialization of init
// IN:	 	none.
// OUT:    	none.
// return:  none.
//------------------------------------------------------------------------------
void SPIS_init(void);

//------------------------------------------------------------------------------
// SPIS_Tx : slave sends a char to master
// IN:	 	char sent to master (unsigned char)
// OUT:    	none.
// return:  none.
//------------------------------------------------------------------------------
void SPIS_Tx(unsigned char);


//------------------------------------------------------------------------------
// SPIS_Rx : slave receive a char to master
// IN:	 	none.
// OUT:    	char sent to master (unsigned char)
// return:  none.
//------------------------------------------------------------------------------
unsigned char SPIS_Rx(void);


#endif /* SPI_Slave_H_ */
