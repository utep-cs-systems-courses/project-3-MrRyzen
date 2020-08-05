# makfile configuration
CPU	      	= msp430g2553
CFLAGS		= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include

# switch the compiler (for internal make rules)
CC		= msp430-elf-gcc
AS		= msp430-elf-gcc -mmcu=${CPU} -c

all: button.elf 

#additional rules for files
main.elf: ${COMMON_OBJECTS} wdt_handler.o stateMachines.o states.o buzzer.o p2_interrupt_handler.o led.o switches.o main.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd -lp2sw

load: main.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf
