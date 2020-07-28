#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "stateMachines.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "states.h"

unsigned char toggle_led;
//Dim variable higher = lower brightness
static char dim = 0;
//Intializes state machine and variables
void state_init() {
  state = 0;
}
//Method resets state machine and variables back to start
void reset_states() {
  state = 0;
  toggle_led = 0;
  buzzer_set_period(0);
  led_update();
}

void drawState() {
  u_char width = screenWidth, height = screenHeight;
  clearScreen(COLOR_BLUE);

  drawString8x12(16,10,"Destroy the", COLOR_WHITE, COLOR_BLUE);
  drawString8x12(28,22,"Triangle", COLOR_WHITE, COLOR_BLUE);
  
  switch (state) {
  case 0:
    drawTriangle((width/2)-36, height/2, 36, COLOR_GREEN);
    break;
  case 1:
    drawTriangle((width/2)-30, height/2, 30, COLOR_GREEN);
    break;
  case 2:
    drawTriangle((width/2)-26, height/2, 26, COLOR_GREEN);
    break;
  case 3:
    drawTriangle((width/2)-12, height/2, 12, COLOR_GREEN);
    break;
  case 4:
    drawTriangle((width/2)-6, height/2, 6, COLOR_RED);
    break;
  }
  P1OUT &= ~LED_GREEN;
  or_sr(0x18);
}

/*void dimmerControl() {
  dim++;
  if (dim == 4)
    return 1;
  else
    return 0;
}*/

void state_advance() {
  //Switch 4 is exit case for all states
  if(sw4_state_down) {
    reset_states();
    play_beep();
  }

  switch (state) {
  case 1:               /* Case 1 set green led and plays beep when sw1 & sw3 are down moves case */
    P1OUT |= LED_GREEN;
    //Led dimmer logic
    if(dimmerControl(dim)){
      toggle_led = LED_RED;
      dim = 0;
    }
    else
      dim++;
    if(sw1_state_down && sw3_state_down) {
      state = 2;
      play_beep();
      drawState();
    }
    break;
  case 2:               /* case 2 sets red led and plays beep when sw2 & sw3 are down moves case */
    P1OUT |= LED_GREEN;
    if(dimmerControl(dim)){
      toggle_led = LED_RED;
      dim = 0;
    }
    else
      dim++;
    if(sw2_state_down && sw3_state_down) {
      state = 3;
      drawState();
    }
    break;
  case 3:               /* Third case dims both leds and plays beep when sw1 & sw2 & sw3 are down moves case */
    P1OUT |= LED_GREEN;
    //Led dimmer logic
    if(dimmerControl(dim)){
      toggle_led = LED_RED;
      dim = 0;
    }
    else
      dim++;
    //wating for next case
    if(sw1_state_down && sw2_state_down && sw3_state_down) {
      state = 4;
      play_beep();
      drawState();
    }
    break;
  case 4:               /* Last case or "win case" sets state to zero to start over and then plays song because you won */
    P1OUT |= LED_GREEN;
    state = 0;
    play_song();//Song player
    drawState();
    break;
  case 0:               /* Base case toggles led with timer intterrupt, moves to case 1 and plays beep if sw1 is down */
    P1OUT |= LED_GREEN;
    if(sw1_state_down) {
      state = 1;
      play_beep();
    }
    break;
  default: break;
  }

  led_update();
}
