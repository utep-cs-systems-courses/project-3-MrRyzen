#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"
#include "states.h"

unsigned char toggle_led, state;
unsigned char redrawScreen = 1;

void drawState() {
  drawString8x12(40,44,stateToString(state), COLOR_WHITE, COLOR_BLUE);
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
}

void main() {
  u_char width = screenWidth, height = screenHeight;
  
  configureClocks();
  //lcd init
  lcd_init();
  // lab 2
  switch_init();
  led_init();
  buzzer_init();
  state_init();

  enableWDTInterrupts();

  or_sr(0x8);

  while(1) { 
    while (!redrawScreen) { /**< Pause CPU if screen doesn't need updating */
      P1OUT &= ~LED_GREEN;    /**< Green led off witHo CPU */
      or_sr(0x10);	      /**< CPU OFF */
    }
    drawState();
    redrawScreen = 0;
    P1OUT |= LED_GREEN;       /**< Green led on when CPU on */
  }
}

/** Watchdog timer interrupt handler. 15 interrupts/sec */
void wdt_c_handler() {
  static char blink_count = 0;
  if (++blink_count == 125) {
    if (state != 3)
      state_advance();    // Calls state advance for all other cases for toggling
    blink_count = 0;
  }
  if (state == 3)
    state_advance();    // Calls state advance for all other cases for toggling
}
