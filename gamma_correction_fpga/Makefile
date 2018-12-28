CROSS_COMPILE ?=

CC	:= $(CROSS_COMPILE)gcc
CFLAGS	?= -O2 -W -Wall 
LDFLAGS	?= -lm

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

all: gamma

gamma: gamma.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f *.mem
	-rm -f *.txt
	-rm -f gamma