//------------------------------------------------------------------------------
// servomotor.h contains prototype of all managing functions for servomotor rotation
//------------------------------------------------------------------------------

#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#include <msp430.h>

#define SERVOMOTOR BIT2
#define SERVOMOTOR_INIT 500
#define SERVOMOTOR_MAX 2500
#define TIME_TO_CHECK 300000
//------------------------------------------------------------------------------
// Servomotor_Init :  called to initialize the ir motor configuration
// IN/OUT:    none.
// return:    none.
//------------------------------------------------------------------------------
void Servomotor_Init(void);

//------------------------------------------------------------------------------
// Servomotor_PWM_Init :  Called to start the pwm signal
// IN/OUT:    none.
// return:    none.
//------------------------------------------------------------------------------
void Servomotor_PWM_Init(void);

//------------------------------------------------------------------------------
// Servomotor_Stop :  stop the motor
// IN/OUT:    none.
// return:    none.
//------------------------------------------------------------------------------
void Servomotor_Stop(void);

//------------------------------------------------------------------------------
// Servomotor_Start :  start the motor
// IN/OUT:    deg (int) degree of rotation.
// return:    int value of TACCR1 to set the rotation.
//------------------------------------------------------------------------------
int Servomotor_Set_Deg(int deg);

//------------------------------------------------------------------------------
// servomotor_sweeping :  realize the sweeping of IR sensor
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void servomotor_sweeping(void);
#endif /* SERVOMOTOR_H_ */
