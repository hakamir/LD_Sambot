//------------------------------------------------------------------------------
// Name:                servomotor.c
//
// Description:         servomotor.c contains functions managing the servomotor
//
// Authors:             Marie DONNET & Rodolphe LATOUR
//
// Version:             1.0
//------------------------------------------------------------------------------

#include "servomotor.h"

//------------------------------------------------------------------------------
// servomotor_Init :  called to initialize the servomotor configuration
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void Servomotor_Init(void)
{
    // Motor management
    Servomotor_Start();

    // PWM init
    Servomotor_PWM_Init();
}

//------------------------------------------------------------------------------
// servomotor_PWM_Init :  Called to start the pwm signal
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void Servomotor_PWM_Init(void)
{
    BCSCTL1 = CALBC1_1MHZ;              // Clock frequency 1MHz
    DCOCTL  = CALDCO_1MHZ;              // Clock frequency 1MHz
    TACTL   = (TASSEL_2 | MC_1 | ID_0);
    TACCTL1 = OUTMOD_7;
    TACCR0  = 20000;
    TACCR1  = SERVOMOTOR_INIT;

    //TACCTL1 |= CCIE;
    __enable_interrupt();               // enable interrupt
}

//------------------------------------------------------------------------------
// servomotor_Stop :  stop the motor
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void Servomotor_Stop(void)
{
    P1DIR &= ~(SERVOMOTOR);
}

//------------------------------------------------------------------------------
// servomotor_Start :  start the motor
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void Servomotor_Start(void)
{
    P1SEL |= SERVOMOTOR;
    P1DIR |= SERVOMOTOR;
}

//------------------------------------------------------------------------------
// servomotor_Set_Deg :  realize the rotation to the degree in parameter
// IN:        deg (int) degree of rotation.
// OUT:       none.
// return:    int value of TACCR1 to set the rotation.
//------------------------------------------------------------------------------
int Servomotor_Set_Deg(int deg)
{
    int taccr = 0;

    // < 45
    if(deg == 0){
        taccr = SERVOMOTOR_MAX / 5;
    // > 0 & < 45
    }else if(deg > 0 && deg <= 45){
        taccr = (2 * SERVOMOTOR_MAX) / 5;
    // > 45 & < 90
    }else if(deg > 45 && deg <= 90){
        taccr = (3 * SERVOMOTOR_MAX) / 5;
    // > 90 & < 135
    }else if(deg > 90 && deg <= 135){
        taccr = (4 * SERVOMOTOR_MAX) / 5;
    // > 135 & 180
    }else if(deg > 135 && deg <= 180){
        taccr = SERVOMOTOR_MAX;
    }

    return taccr;
}
