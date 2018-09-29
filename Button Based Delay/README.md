# Lab 1: Button Based Delay

## Summary
 There are two programs made for two different boards the MSP430F5529 and the MSP430G2553. Each of the programs start with a standard blinking light with a certain speed with a button that can be held down to set the LED to blink at a different rate equivalent to the length the user holds the button.

## General Functionality
 The two programs start the boards LEDs blinking at a certain speed then switches using interrupts to set a new light blinking rate for the LED using the ACLK. This is done using a state machine the first state is basic blink where the LED is blinking at the initial rate. The next state is entered when you press the button the interrupt is flagged and the timer starts to count on continuous mode to find the desired length of delay. This state will also turn on the Red LED showing that the microcontroller is this state. The last state detects when the button is finally released the timer is stopped , cleared, set back to Up timer and the interrupt flags are unset. Then it is brought back to blinking mode using this different blink rate.
 
## Inputs and Outputs

### MSP430F5529
 INPUTS: P1.1-Tactile Button
 OUTPUTS: P1.0- Red LED, P4.7-Green LED
 
### MSP430G2553
 INPUTS: P1.3-Button  
 OUTPUTS: P1.0-Green LED, P1.6-Red LED
 
## Authors

   Author: Kieran O'Connor  
   Last Editted: 9/28/2018
   
# Button Based Delay
Now that you have begun to familiarize yourself with the TIMER modules, why don't we make an interesting change to our code from the last lab.

## Task
Setup your microcontroller to initially blink and LED at a rate of 10Hz upon restarting or powering up. Then utilizing one of the buttons on board, a user should be able to set the delay or blinking rate of the LED by holding down a button. The duration in which the button is depressed should then become the new rate at which the LED blinks. As previously stated, you most likely will want to take advantage of the fact that TIMER modules exist and see if you can let them do a bulk of the work for you.

### Extra Work
## Reset Button
What is a piece of electronics without a reset button? Instead of relying on resetting your processor using the built in reset circuitry, why not instead use another button to reset the rate back to 10Hz.

## Button Based Hertz
Most likely using two buttons, what if instead of making a delay loop based on the time, the user could instead enter a mode where the number of times they pressed the button would become the number in Hz of the blinking rate? How do you think you would implement that with just one button?
