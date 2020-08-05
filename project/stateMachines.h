#ifndef stateMachine_included
#define stateMachine_included
//state variable
extern unsigned char state, redrawScreen;

void state_init();
void state_advance();
void drawState();

#endif // included
