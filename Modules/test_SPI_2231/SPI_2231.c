/*
 * -----------------------------------------------------
 *  P R O G R A M M A T I O N   S P I   E S I G E L E C
 *
 * Lauchpad v1.5 support
 *
 * MSP430G2231 - SPI/SLAVE 3 Wires
 *
 * (c)-Yann DUCHEMIN / ESIGELEC - r.III132018 for CCS
 * --------------------------------------------------------------
 * La carte Launchpad est raccordée en SPI via l'USI B0
 * 		SCLK : P1.5 / SCLK
 * 		SIMO : P1.7 / SDA
 * 		MOSI : P1.6	/ SDO
 *
 * A la reception du caractère 1 la LED Rouge P1.0 est allumée
 *
 * A la reception du caractère 0 la LED Rouge P1.0 est eteinte
 *
 */
#include <msp430.h> 
#include <intrinsics.h>

volatile unsigned int RXDta;

/*
 * main.c
 */
void main( void )
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW | WDTHOLD;

    if(CALBC1_1MHZ==0xFF || CALDCO_1MHZ==0xFF)
    {
        __bis_SR_register(LPM4_bits);
    }
    else
    {
        // Factory Set.
        DCOCTL = 0;
        BCSCTL1 = CALBC1_1MHZ;
        DCOCTL = (0 | CALDCO_1MHZ);
    }

    //--------------- Secure mode
    P1SEL = 0x00;        // GPIO
    P1DIR = 0x00;         // IN

    // led
    P1DIR |=  BIT0;
    P1OUT &= ~BIT0;

    // USI Config. for SPI 3 wires Slave Op.
    // P1SEL Ref. p41,42 SLAS694J used by USIPEx
    USICTL0 |= USISWRST;
    USICTL1 = 0;

    // Slave Mode SLAU144J 14.2.3.2 p400
    USICTL0 &= ~(USIMST);
    USICTL1 &= ~(USII2C);

    // 3 wire, mode Clk&Ph / 14.2.3 p400
    USICTL0 |= (USIPE7 | USIPE6 | USIPE5 | USILSB | USIOE | USIGE );
    USICTL1 |= USIIE;
    USICTL1 &= ~USICKPH;

    USICKCTL = 0; 			// No Clk Src in slave mode
    USICKCTL &= ~(USICKPL);	// Polarity

    USICNT &= ~(USI16B | USIIFGCC | USISCLREL); // Only lower 8 bits used 14.2.3.3 p 401 slau144j
    USISRL = 0x23;	// hash, just mean ready; USISRL Vs USIR by ~USI16B set to 0
    USICNT = 0x08;

    __bis_SR_register(LPM4_bits | GIE); // general interrupts enable & Low Power Mode

    // Wait for the SPI clock to be idle (low).
    while ((P1IN & BIT5)) ;

    USICTL0 &= ~USISWRST;
    USICTL0 &= ~USISWRST;


}

void SPIS_init(void)
{
    if(CALBC1_1MHZ==0xFF || CALDCO_1MHZ==0xFF)
    {
        __bis_SR_register(LPM4_bits);
    }
    else
    {
        // Factory Set.
        DCOCTL = 0;
        BCSCTL1 = CALBC1_1MHZ;
        DCOCTL = (0 | CALDCO_1MHZ);
    }

    //--------------- Secure mode
    P1SEL = 0x00;        // GPIO
    P1DIR = 0x00;         // IN

    // USI Config. for SPI 3 wires Slave Op.
    // P1SEL Ref. p41,42 SLAS694J used by USIPEx
    USICTL0 |= USISWRST;
    USICTL1 = 0;

    // 3 wire, mode Clk&Ph / 14.2.3 p400
    // SDI-SDO-SCLK - LSB First - Output Enable - Transp. Latch
    USICTL0 |= (USIPE7 | USIPE6 | USIPE5 | USILSB | USIOE | USIGE );

    // Slave Mode SLAU144J 14.2.3.2 p400
    USICTL0 &= ~(USIMST);
    USICTL1 |= USIIE;
    USICTL1 &= ~(USICKPH | USII2C);

    USICKCTL = 0;           // No Clk Src in slave mode
    USICKCTL &= ~(USICKPL | USISWCLK);  // Polarity - Input ClkLow

    USICNT = 0;
    USICNT &= ~(USI16B | USIIFGCC ); // Only lower 8 bits used 14.2.3.3 p 401 slau144j
    USISRL = 0x23;  // hash, just mean ready; USISRL Vs USIR by ~USI16B set to 0
    USICNT = 0x08;

    // Wait for the SPI clock to be idle (low).
    while ((P1IN & BIT5)) ;

    USICTL0 &= ~USISWRST;
}


unsigned char SPIS_Rx(void)
{
	USICNT &= ~USI16B;  // re-load counter & ignore USISRH
	USICNT = 0x08;      // 8 bits count, that re-enable USI for next transfert
	return USISRL;
}

/*void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

    servomotor_init();
    SPIS_init();

    __bis_SR_register(LPM4_bits | GIE);		// general interrupts enable & Low Power Mode
    while(1);
}*/

// Echo back RXed character, confirm TX buffer is ready first
/*#pragma vector=USI_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	while( !(USICTL1 & USIIFG) );   // waiting char by USI counter flag

    unsigned char c = SPIS_Rx();
    switch (c)
    {
    case '0' :
        servomotor_set_deg(0);
        __delay_cycles(TIME_TO_CHECK);
        break;

    case '1' :
        servomotor_set_deg(45);
        __delay_cycles(TIME_TO_CHECK);
        break;

    case '2' :
        servomotor_set_deg(90);
        __delay_cycles(TIME_TO_CHECK);
        break;

    case '3' :
        servomotor_set_deg(135);
        __delay_cycles(TIME_TO_CHECK);
        break;

    case '4' :
        servomotor_set_deg(180);
        __delay_cycles(TIME_TO_CHECK);
        break;
    }
}*/

// --------------------------- R O U T I N E S   D ' I N T E R R U P T I O N S

/* ************************************************************************* */
/* VECTEUR INTERRUPTION USI                                                  */
/* ************************************************************************* */
#pragma vector=USI_VECTOR
__interrupt void universal_serial_interface(void)
{
	while( !(USICTL1 & USIIFG) );   // waiting char by USI counter flag

	RXDta = USISRL;
	USICNT &= ~USI16B;  // re-load counter
	// USISRL = 0x23;
	USICNT = 0x08;      // 8 bits count, that re-enable USI for next transfer

	if (0x30 & RXDta) //if the input buffer is 0x30 (mainly to read the buffer)
	{
		P1OUT |= BIT0; //turn on LED
	}
	else if (0x31 & RXDta)
	{
		P1OUT &= ~BIT0; //turn off LED
	}
}
//------------------------------------------------------------------ End ISR


/*void servomotor_init(void)
{
	// Motor management
	P1SEL |= BIT2;
	P1DIR |= BIT2;

	// PWM init
	servomotor_PWM_init();

	TACCR1 = servomotor_set_deg(0);   // initialization to 0 deg
	__delay_cycles(TIME_TO_CHECK*4);

}

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
}*/
