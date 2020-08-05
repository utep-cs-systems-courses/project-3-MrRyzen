#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"

char sw1_state_down, sw2_state_down, sw3_state_down, sw4_state_down; /* effectively boolean */
int redrawScreen;

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		  /* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}

void
switch_interrupt_handler() {
  char p2val = switch_update_interrupt_sense();

   if (p2val & SW1 ? 0 : 1){ //used if p2val and SW1 is true (button 1 is pressed)
    sw1_state_down = 1;
    redrawScreen = 1;
  }
  else if (p2val & SW2 ? 0 : 1){ //used if p2val and SW2 is true (button 2 is pressed)
    sw2_state_down = 1;
    redrawScreen = 1;
  }
  else if (p2val & SW3 ? 0 : 1){ //used if p2val and SW3 is true (button 3 is pressed)
    sw3_state_down = 1;
    redrawScreen = 1;
  }
  else if (p2val & SW4 ? 0 : 1){ //used if p2val and SW4 is true (button 4 is pressed)
    sw4_state_down = 1;
    redrawScreen = 1;
  }
  else {
    clearWindow();              //clear window after interrupt
    sw1_state_down = 0;
    sw2_state_down = 0;
    sw3_state_down = 0;
    sw4_state_down = 0;   //set state back to 0
  }
}
