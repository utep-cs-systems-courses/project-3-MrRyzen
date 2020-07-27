#include <msp430.h>
#include "../timerLib/libTimer.h"
#include "buzzer.h"
#include "stateMachines.h"

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

//Method to play beep indicating moving case
void play_beep() {
  
  buzzer_set_period(750);
  __delay_cycles(5000000);

  buzzer_set_period(0); // silence buzzer
  return;
}

//Method to play a song
void play_song() {
  short A2 = 233.08;	/* notes for the song */
  short B2 = 246.94;
  short A = 440.00;
  short D = 293.66;
  short F = 349.23;
  short G2 = 415.30;
  short G = 392.00;
  
  /* Quick little song tried to play megolavania
  but this song wasnt too bad so i kept it */
  int song[22] = {D, D, D, A, G2, G, F, D, F, G, 0,
		  D, D, D, A, G2, G, F, D, F, G, 0};
  
  //Play song with delay between notes
  for (int i = 0; i < 22; i++) {
    buzzer_set_period(song[i]);
    __delay_cycles(5000000);
  }

  buzzer_set_period(0); // silence buzzer
  return;
}


    
    
  

