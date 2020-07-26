#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
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

  fillRectangle(30,30, 60, 60, COLOR_ORANGE);

  // from p2sw-demo
  p2sw_init(15);
  or_sr(0x8); // GIE (enable interrupts)
  
  //lab 2
  switch_init();
  led_init();
  buzzer_init();
  enableWDTInterrupts();

  state_init();
  
  or_sr(0x18);
} 
