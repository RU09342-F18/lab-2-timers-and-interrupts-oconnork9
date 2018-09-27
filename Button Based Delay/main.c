#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	BCSCTL3 = LFXT1S_2;
	
	P1DIR |= BIT0;
	P1OUT |= BIT0;

	P1DIR |= BIT6;
	P1OUT &=~BIT6;

	P1DIR &=~BIT3;
	P1OUT |= BIT3;
	P1REN |= BIT3;

	TA0CTL=TASSEL_1 + MC_1 + ID_3;
	CCTL0 = CCIE;
	CCR0 = 250;
	P1IE |= BIT3;
	P1IES |=BIT3;
	P1IFG &=~BIT3;
	_BIS_SR(LPM0_bits + GIE);
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{

    P1OUT ^= 0x01;

}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(P1IES & BIT3)
    {
       P1IES &= ~BIT3;
       TA0CTL = TACLR;
       TA0CTL = TASSEL_1 + MC_2 + ID_3;
       P1OUT |= BIT6;
    }
    else
    {
       P1OUT &=~ BIT6;
       TA0CTL = MC_0;
       CCR0 = TA0R;
       TA0CTL = TACLR;
       TA0CTL = TASSEL_1 + MC_1 + ID_3;
       P1IES |=BIT3;
    }

    P1IFG &=~ BIT3;

}
