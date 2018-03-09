CC=gcc
CFLAGS= -Wall -Wextra -pedantic -I.
OBJS=main.o prog_cb.o underworld_cb.o bp_handler.o debug_functions.o debug_primes.o
EXEC=ptrace
INC=ptrace.h

all: clean $(EXEC)

%.o: %.c $(INC)
	$(CC) -c -o $@ $<

$(EXEC) : $(OBJS) 
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

clean:
	rm -rf *.o
	rm -rf $(EXEC)
