#include <msp430.h>
#include "stateMachines.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if (++blink_count == 15) {
    state_advance();    // Calls state advance for all other cases for toggling
    blink_count = 0;
  }
}
