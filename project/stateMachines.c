#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"

unsigned char toggle_led;
//Dim variable higher = lower brightness
static char dim = 0;
//Intializes state machine and variables
void state_init() {
  state = 0;
  redrawScr = 1;
  //toggle_led = (toggle_led & LED_RED) ? LED_GREEN : LED_RED;
  led_update();
}
//Method resets state machine and variables back to start
void reset_states() {
  state = 0;
  toggle_led = 0;
  buzzer_set_period(0);
  led_update();
}

void state_advance() {
  //Switch 4 is exit case for all states
  if(sw4_state_down) {
    reset_states();
    play_beep();
  }
  //Dimming for case 3 only
  dim++;
  dim = (dim > 8) ? 0 : dim;

  switch (state) {
  case 1:               /* Case 1 set green led and plays beep when sw1 & sw3 are down moves case */
    //toggle_led = LED_GREEN;
    clearScreen(COLOR_RED);
    redrawScreen = 1;
    if(sw1_state_down && sw3_state_down) {
      state = 2;
      play_beep();
    }
    break;
  case 2:               /* case 2 sets red led and plays beep when sw2 & sw3 are down moves case */
    //toggle_led = LED_RED;
    if(sw2_state_down && sw3_state_down) {
      state = 3;
    }
    break;
  case 3:               /* Third case dims both leds and plays beep when sw1 & sw2 & sw3 are down moves case */
    /*Led dimmer logic
    if (dim == 0)
      toggle_led = LED_GREEN | LED_RED;
    else
      toggle_led = 0;*/
    //wating for next case
    if(sw1_state_down && sw2_state_down && sw3_state_down) {
      state = 4;
      play_beep();
    }
    break;
  case 4:               /* Last case or "win case" sets state to zero to start over and then plays song because you won */
    state = 0;
    play_song();//Song player
    break;
  case 0:               /* Base case toggles led with timer intterrupt, moves to case 1 and plays beep if sw1 is down */
    if(sw1_state_down) {
      state = 1;
      clearScreen(COLOR_ORANGE);
      redrawScr = 1;
      play_beep();
    }
    //toggle_led = (toggle_led & LED_RED) ? LED_GREEN : LED_RED;//Toggles leds
    break;
  default: break;
  }

  led_update();
}
