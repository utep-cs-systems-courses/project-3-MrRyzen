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

  drawString8x12 (16,10,"Destroy the", COLOR_WHITE, COLOR_BLUE);
  drawString8x12 (28,22,"Triangle", COLOR_WHITE, COLOR_BLUE);
  
  for (int row = 1; row < 51; row++) {
    for (int col = 1; col < (row+(row-1)); col++) {
      drawPixel((col+15)+(50-row), row+35, COLOR_ORANGE);
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
