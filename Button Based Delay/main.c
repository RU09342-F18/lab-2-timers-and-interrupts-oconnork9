#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer


    P1DIR |= BIT0; //Sets P1.0 as Output
    P1OUT |= BIT0; //Turns on P1.0

    P4DIR |= BIT7; //Sets P1.6 as Output
    P4OUT &=~BIT7; //Turns off P1.6

    P1DIR &=~BIT1; //Sets P1.3 as Input
    P1OUT |= BIT1; //Sets Resistor as Pull-up Resistor
    P1REN |= BIT1; //Sets Resistor on P1.3

    TA0CTL=TBSSEL_1 + MC_1 + ID_3; //Sets Timer0 as ACLK, UP, and 8 Divider
    TA0CCTL0 = CCIE; //Interrupt Enabled
    TA0CCR0 = 500; //Sets Clock count
    P1IE |= BIT1; //Interrupt
    P1IES |=BIT1; //Sets Interrupt as activated by negative clock edge
    P1IFG &=~BIT1; //Clears Interrupt Flags
    _BIS_SR(LPM0_bits + GIE); //Low power mode 0 enabled and Global Interrupt
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)
{

    P1OUT ^= BIT0; //Flashes P1.0 Green LED

}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(P1IES & BIT1) //Checks if Button is being held down
    {
       P1IES &= ~BIT1; //Sets Interrupt as activated by positive clock edge
       TA0CTL = TACLR; //Clears Timer0
       TA0CTL = TASSEL_1 + MC_2 + ID_3; //Sets Timer as ACLK, Continuous, and 8 Divider
       P4OUT |= BIT7; //Holds Red LED P1.6 on to signal the user what state the
    }
    else
    {
       P4OUT &=~ BIT7; //Turns off Red LED P1.6
       TA0CTL = MC_0; //Stops Timer
       TA0CCR0 = TA0R; //Sets range of UP Timer to the held down time of Button
       TA0CTL = TACLR; //Clears Timer
       TA0CTL = TASSEL_1 + MC_1 + ID_3; //Sets Timer to ACLK, UP, and 8 Divider
       P1IES |=BIT1; //Sets Interrupt as activated by negative clock edge
    }

    P1IFG &=~ BIT1; //Unsets Interrupt Flag

}
