#ifndef stateMachine_included
#define stateMachine_included
//state variable
extern unsigned char state;
extern char redrawScreen;

void state_init();
void state_advance();

#endif // included
