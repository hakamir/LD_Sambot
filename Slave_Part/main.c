//------------------------------------------------------------------------------
// Name:                Bus Slave
//
// Description:         Shall allow SPI communication between MSP430G2553 (MASTER)
//                      and MSP430G2231 (SLAVE).
//
// Authors:             Marie DONNET / Rodolphe Latour
//
// Version:             1.0
//------------------------------------------------------------------------------

#include <msp430.h>

#include "servomotor.h"

//------------------------------------------------------------------------------
// main:    call each init functions and wait for ever.
//------------------------------------------------------------------------------
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer

  //InitPort();                           // Initialize Ports
  //SPI_Init();                           // Initialize SPI connection
  Servomotor_Init();                      // Set pwm for ir motor

  //_BIS_SR(LPM0_bits + GIE);           // Enter LPM0 w/ interrupt

  while(1)
  {
      TACCR1 = Servomotor_Set_Deg(45);
      TACCR1 = Servomotor_Set_Deg(90);
      TACCR1 = Servomotor_Set_Deg(135);
      TACCR1 = Servomotor_Set_Deg(180);
      TACCR1 = Servomotor_Set_Deg(135);
      TACCR1 = Servomotor_Set_Deg(90);
      TACCR1 = Servomotor_Set_Deg(45);
      TACCR1 = Servomotor_Set_Deg(0);
  }
}

//------------------------------------------------------------------------------
// USI_VECTOR:  interruption when SPI buffer is updated
//------------------------------------------------------------------------------
#pragma vector=USI_VECTOR
__interrupt void universal_serial_interface(void)
{
    //SPI_Receive_Data();

    // send check begin
    //SPI_Send_Data('C');

    // check begin
    TACCR1 = Servomotor_Set_Deg(0);   // set to 0 deg
    __delay_cycles(TIME_TO_CHECK);
    TACCR1 = Servomotor_Set_Deg(45);  // set to 45 deg
    __delay_cycles(TIME_TO_CHECK);
    TACCR1 = Servomotor_Set_Deg(90);  // set to 45 deg
    __delay_cycles(TIME_TO_CHECK);
    TACCR1 = Servomotor_Set_Deg(135); // set to 135 deg
    __delay_cycles(TIME_TO_CHECK);
    TACCR1 = Servomotor_Set_Deg(180); // set to 180 deg
    __delay_cycles(TIME_TO_CHECK);

    USICNT = 8;                    // re-load counter
}

