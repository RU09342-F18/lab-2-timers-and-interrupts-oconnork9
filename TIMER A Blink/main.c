#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	BCSCTL3 = LFXT1S_2;
	
	P1DIR |= BIT0;
	P1DIR |= BIT6;

	P1OUT |= BIT0;
	P1OUT |= BIT6;

	TA1CCTL0 |= CCIE;
	TA0CCTL0 |= CCIE;
	TA0CTL=TASSEL_2+MC_1+ID_3;
	TA1CTL=TASSEL_2+MC_1+ID_3;

	TA1CCR0=50000;
	TA0CCR0=10000;

	_BIS_SR(LPM0_bits + GIE);
}
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)
{
    P1OUT ^= BIT0;
}
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0(void)
{
    P1OUT ^= BIT6;
}
