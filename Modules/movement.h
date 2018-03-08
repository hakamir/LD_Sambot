//******************************************************************************
//   
//	This is the header of the module movement.c
//	It contains the function move() and stop()
//
//
//                  	  		 	MSP430G2553
//                	   			 -----------------
//        	 	        	   -|VCC           GND|- 
//        	 	        	   -|P1.0          XIN|-
//	 	  	   Data In (UART) <-|P1.1         XOUT|- 
//		 	  Data OUT (UART) <-|P1.2         TEST|- 
//      	        		  <-|P1.3          RST|--->
// Serial Clock Out (UCA0CLK) <-|P1.4         P1.7|-> Data Out (UCA0SIMO)
//  			  Slave reset <-|P1.5         P1.6|<- Data In (UCA0SOMI)
//		 		   odometer A <-|P2.0         P2.5|-> Sense Motor B
//	  		  	Sense Motor A <-|P2.1         P2.4|-> PWM Motor B
// 				  PWM Motor A <-|P2.2         P2.3|-> odometer B
//								 -----------------
//
//   Rodolphe LATOUR
//   March 2018
//******************************************************************************


//******************************************************************************
//	 		 move :	This function initializes the ports of the device connected on
//	the motherboard. (Odometers, motors and sense of rotation)
//			input :	N/A
//   	   output :	N/A
//******************************************************************************
void init_move();

//******************************************************************************
//	 		 move :	This function initializes the port P1.1 where the IR sensor
//	is connected and initialize the ADC. 
//			input :	- enum {FORWARD, BACKWARD, LEFT, RIGHT} -> direction of the robot
//					- int -> speed of the left motor
//					- int -> speed of the right motor
//   	   output :	N/A
//******************************************************************************
void move();

//******************************************************************************
//	 		 stop :	This function stops both motors and do not change the sense of rotation
//			input :	N/A
//   	   output :	N/A
//******************************************************************************
void stop();

void init_timer_A1();
