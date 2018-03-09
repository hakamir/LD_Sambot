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


#include "UART.h"
#include "measure.h"

//------------------------------------------------------------------------------
// main:    call each init functions and wait for ever.
//------------------------------------------------------------------------------
void IR_UART(void)
{
  WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer

  int mes; 					// measure of distance between IR sensor and object (value between 0 and 1023)
  int mes_mm;				// measure of distance between IR sensor and object in millimeters (value between 40 and 300)
  char mes_send = 'A';		// measure of distance between IR sensor and object in millimeters convert in char to send with UART

  init_UART();
  measure_init();
  mes = measure();

  mes_mm = convert_measure(mes);

  mes_send = mes_mm;

  TX_UART(mes_send);		// Send of meausre with UART

}

