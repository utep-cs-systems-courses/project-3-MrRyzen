#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"

unsigned char redrawScreen, toggle_led;

void drawInit() {
  clearScreen(COLOR_BLUE);

  drawString8x12(16,10,"Destroy the", COLOR_WHITE, COLOR_BLUE);
  drawString8x12(28,22,"Triangle", COLOR_WHITE, COLOR_BLUE);
}

void lcdRedraw() {
  u_char width = screenWidth, height = screenHeight;
  drawTriangle((width/2)-36, height/2, 36, COLOR_ORANGE);
}

void main(void) {
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

  drawInit();

  for(;;){
    while(!redrawScreen){
      toggle_led = LED_RED;
      led_update();
      or_sr(0x10);
    }
    toggle_led = LED_GREEN;
    led_update();
    
    lcdRedraw();
    redrawScreen = 0;
  }
}
