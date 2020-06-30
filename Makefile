CC=gcc
CFLAGS=-I.
DEPS = conio.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: main.o conio.o 
	$(CC) -o main main.o conio.o 

clean:
	rm main main.o conio.o