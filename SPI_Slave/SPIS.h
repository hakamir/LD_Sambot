//------------------------------------------------------------------------------
// Name:                SPIS.c
//
// Description:         SPIS.c contains functions managing the servomotor
//
// Authors:             Marie DONNET & Rodolphe LATOUR
//
// Version:             1.0
//------------------------------------------------------------------------------

#include "SPIS.h"

//------------------------------------------------------------------------------
// servomotor_Init :  called to initialize the servomotor configuration
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void Servomotor_Init(void)
{
	// Motor management
	P1SEL |= SERVOMOTOR;
	P1DIR |= SERVOMOTOR;

	// PWM init
	Servomotor_PWM_Init();

}
