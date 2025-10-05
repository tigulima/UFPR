CC = gcc
CFLAGS = -Wall -g

all: gbv

gbv: main.o gbv.o util.o
	$(CC) $(CFLAGS) -o gbv main.o gbv.o util.o

main.o: main.c gbv.h
	$(CC) $(CFLAGS) -c main.c

gbv.o: gbv.c gbv.h
	$(CC) $(CFLAGS) -c gbv.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

clean:
	rm -f *.o gbv

