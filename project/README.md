# Project 2 - Blinky Buzzy Toy

Simple toy on the MSP430 uses a state machine to control the state of the toy changed with buttons.

## Running the Program

To compile and run the program on the MSP430, use:

**$ make load**

To clean any unnecessary or temporary files from the project directory:

**$ make clean**

## State Machine

The state machines starts at state 0 whichs toggles both leds. Moving between the states
requires either SW1 or SW2 or SW3 while SW4 causes and exit state at all states which just
resets the state machine back to the base case. Overall logic is documented below.

0. Base State
   - LEDs toggle on and off between RED and GREEN.
   - Must click SW 1 to advance.
   - Plays beep on advance
1. State 1
   - LEDs on GREEN.
   - Must click SW 1 & SW 3 to advance.
   - Plays beep on advance
2. State 2
   - LEDs on RED.
   - Must click SW 2 & SW 3 to advance.
   - No beep on advance
3. State 3
   - LEDs on RED & GREEN both dim.
   - Must click SW 1 & SW2 & SW3 to advance.
   - Plays beep on advance
4. State 4
   - No LEDs on.
   - Auto advance to state 0.
   - Plays song.
5. Exit State
   - No LEDs on.
   - Auto advance to state 0.
   - Turns off buzzer.
   - Resets variables for clean game start.
   - Plays beep when done.