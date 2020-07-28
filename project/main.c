#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "stateMachines.h"

unsigned char toggle_led, state, redrawScreen;

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
    drawTriangle((width/2)-36, height/2, 12, COLOR_GREEN);
    break;
  case 4:
    drawTriangle((width/2)-36, height/2, 6, COLOR_RED);
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

  drawState();

  toggle_led = LED_RED;//led off
  led_update();

  or_sr(0x18);

  while (1) {
    while (!redrawScreen) {
      toggle_led = LED_RED;
      led_update();
      or_sr(0x18);
    }
    toggle_led = LED_GREEN;
    led_update();

    drawState();
    redrawScreen = 0;
  }
}