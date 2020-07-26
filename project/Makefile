# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: button.elf 

#additional rules for files
main.elf: ${COMMON_OBJECTS} wdInterruptHandler.o stateMachines.o buzzer.o p2_interrupt_handler.o led.o switches.o main.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lLcd -lp2sw -lTimer

load: main.elf
	msp430loader.sh main.elf

clean:
	rm -f *.o *.elf
