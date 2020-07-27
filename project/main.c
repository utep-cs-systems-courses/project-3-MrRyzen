#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"

char redrawScreen;

void main(void) {
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

  clearScreen(COLOR_BLUE);

  drawString8x12(16,10,"Destroy the", COLOR_WHITE, COLOR_BLUE);
  drawString8x12(28,22,"Triangle", COLOR_WHITE, COLOR_BLUE);

  for(;;){
    while(!redrawScreen){
      P1OUT &= ~LED_RED;
      or_sr(0x10);
    }
    P1OUT |= LED_GREEN;
    redrawScreen = 0;

    drawTriangle((width/2)-36, height/2, 36, COLOR_ORANGE);
  }
}
