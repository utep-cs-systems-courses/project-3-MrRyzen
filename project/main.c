#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>

void main(void) {  
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);
  clearScreen(COLOR_NAVY);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);
  drawString8x12 (10,10,"Howdy", COLOR_WHITE, COLOR_SKY_BLUE);

  fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  
  /*switch_init();
  led_init();
  buzzer_init();
  enableWDTInterrupts();

  state_init();
  
  or_sr(0x18);  */
} 