#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "stateMachines.h"

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  led_update();
}

void led_update(){
  char ledFlags = 0; /* by default, no LEDs on */
  
  ledFlags = toggle_led;// sets led flags with toggle_led changed in stateMachines

  P1OUT &= (0xff - LEDS) | ledFlags; // clear bits for off leds
  P1OUT |= ledFlags;         // set bits for on leds
}

