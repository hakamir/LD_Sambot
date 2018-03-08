

#include <msp430.h>

volatile char received_ch = 0;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD; // Stop watchdog timer

	if(CALBC1_1MHZ==0xFF || CALDCO_1MHZ==0xFF)
	{
		__bis_SR_register(LPM4_bits);
	}
	else
	{
		BCSCTL1 = CALBC1_1MHZ;
		DCOCTL = CALDCO_1MHZ;
	}

	P1OUT |= BIT4;
	P1DIR |= BIT4;

	P1SEL |= (BIT5 + BIT6 + BIT7);
	P1SEL2 |= (BIT5 + BIT6 + BIT7);

	UCB0CTL1 = UCSWRST;

	UCB0CTL0 |= UCCKPL + UCCKPH + UCMSB + UCMST + UCSYNC;
	UCB0CTL1 |= UCSSEL_2;

	UCB0BR0 = 0x02;
	UCB0BR1 = 0x00;

	UCB0CTL1 = 0x00;

	P1OUT &= ~BIT4;

	while(!(IFG2 & UCA0TXIFG));
		UCB0TXBUF = 0xA2;
		__delay_cycles(50);
	while(!(IFG2 & UCA0RXIFG));
		received_ch = UCB0RXBUF;
	
	P1OUT |= BIT4;
}
