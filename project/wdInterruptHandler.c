#include <msp430.h>
#include "led.h"
#include "stateMachines.h"

unsigned char state;

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  P1OUT |= LED_GREEN;
  static char blink_count = 0;
  if (++blink_count == 15) {
    state_advance();    // Calls state advance for all other cases for toggling
    blink_count = 0;
  }
  P1OUT &= ~LED_GREEN;
}
