#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"

void main(void) {  
  configureClocks();
  //lcd init
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);
  clearScreen(COLOR_NAVY);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);
  drawString8x12 (10,10,"Howdy", COLOR_WHITE, COLOR_SKY_BLUE);
  
  for (int col = 0; col < 20; col++) {
    for (int row = 0; row < col; row++) {
      void drawPixel(col, row, COLOR_ORANGE);
    }
  }

  /* lab 2
  switch_init();
  led_init();
  buzzer_init();
  enableWDTInterrupts();

  state_init();
  
  or_sr(0x18);*/
} 
