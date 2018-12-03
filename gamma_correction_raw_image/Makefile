CROSS_COMPILE ?=

CC	:= $(CROSS_COMPILE)gcc
CFLAGS	?= -O2 -W -Wall 
LDFLAGS	?= -lm

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

all: gamma_correction

gamma_correction: gamma_correction.o
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	-rm -f *.o
	-rm -f gamma_correction
	-rm -f gamma_corrected.raw