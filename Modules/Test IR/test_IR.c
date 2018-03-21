#include <msp430.h>
#include "measure.h"

int distance; 
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    measure_init();
	distance = measure();

}
