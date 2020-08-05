#include <msp430.h>
#include "led.h"
#include "stateMachines.h"
#include <libTimer.h>
unsigned char state, redrawState;

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if (++blink_count == 125) {
    if (state != 3)
      state_advance();    // Calls state advance for all other cases for toggling
    blink_count = 0;
  }
  if (state == 3)
    state_advance();    // Calls state advance for all other cases for toggling
  if(redrawScreen)
    and_sr(~0x10);
}
