//******************************************************************************
// Name:                servomotor.c
//
// Description:         servomotor.c contains functions managing the servomotor
//
//
//
//
//                  	  		 	MSP430G2231
//                	   			 -----------------
//        	 	        	   -|VCC           GND|- 
//        	 	        	   -|P1.0          XIN|-
//	 	  	   				   -|P1.1         XOUT|- 
//		 	  		Stepmotor <-|P1.2         TEST|- 
//      	       			  <-|P1.3          RST|--->
// Serial Clock Out (UCA0CLK) <-|P1.4         P1.7|-> Data Out (UCA0SIMO)
//  			  Slave reset ->|P1.5         P1.6|<- Data In (UCA0SOMI)
//								 -----------------
//
//
//   Rodolphe LATOUR
//	 Marie DONNET
//   March 2018
//******************************************************************************


#include "servomotor.h"
//#include "SPIS.h"

//------------------------------------------------------------------------------
// servomotor_Init :  called to initialize the servomotor configuration
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void servomotor_init(void)
{
	// Motor management
	P1SEL |= SERVOMOTOR;
	P1DIR |= SERVOMOTOR;

	// PWM init
	servomotor_PWM_init();

}

//------------------------------------------------------------------------------
// servomotor_PWM_Init :  Called to start the pwm signal
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void servomotor_PWM_init(void)
{
	BCSCTL1 = CALBC1_1MHZ;              // Clock frequency 1MHz
	DCOCTL  = CALDCO_1MHZ;              // Clock frequency 1MHz
	TACTL   = (TASSEL_2 | MC_1 | ID_0);
	TACCTL1 = OUTMOD_7;
	TACCR0  = 20000;					// 20ms, 50Hz
	TACCR1  = SERVOMOTOR_INIT; 			// 500


	//TACCTL1 |= CCIE;
	//__enable_interrupt();               // enable interrupt
}

//------------------------------------------------------------------------------
// servomotor_Stop :  stop the motor
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void servomotor_stop(void)
{
	P1DIR &= ~(SERVOMOTOR);
}

//------------------------------------------------------------------------------
// servomotor_set_deg :  realize the rotation to the degree in parameter
// IN:        deg (int) degree of rotation.
// OUT:       none.
// return:    int value of TACCR1 to set the rotation.
//------------------------------------------------------------------------------
int servomotor_set_deg(int deg)
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


//------------------------------------------------------------------------------
// servomotor_sweeping :  realize the sweeping of IR sensor
// IN:        none.
// OUT:       none.
// return:    none.
//------------------------------------------------------------------------------
void servomotor_sweeping(void)
{
	servomotor_init();                      // Set pwm for ir motor

	TACCR1 = servomotor_set_deg(0);   // initialization to 0 deg
	__delay_cycles(TIME_TO_CHECK*4);

	TACCR1 = servomotor_set_deg(0);   // set to 0 deg
	//SPIS_Tx('0');
	__delay_cycles(TIME_TO_CHECK);
	TACCR1 = servomotor_set_deg(45);  // set to 45 deg
	//SPIS_Tx('45');
	__delay_cycles(TIME_TO_CHECK);
	TACCR1 = servomotor_set_deg(90);  // set to 90 deg
	//SPIS_Tx('90');
	__delay_cycles(TIME_TO_CHECK);
	TACCR1 = servomotor_set_deg(135); // set to 135 deg
	//SPIS_Tx('135');
	__delay_cycles(TIME_TO_CHECK);
	TACCR1 = servomotor_set_deg(180); // set to 180 deg
	//SPIS_Tx('180');
	__delay_cycles(TIME_TO_CHECK);
	TACCR1 = servomotor_set_deg(135);  // set to 135 deg
	//SPIS_Tx('135');
	__delay_cycles(TIME_TO_CHECK);
	TACCR1 = servomotor_set_deg(90);  // set to 90 deg
	//SPIS_Tx('90');
	__delay_cycles(TIME_TO_CHECK);
	TACCR1 = servomotor_set_deg(45); // set to 45 deg
	//SPIS_Tx('45');
	__delay_cycles(TIME_TO_CHECK);
}
