CC=gcc
CFLAGS=-c
LFLAGS=-L.
OPTIM=-O3
DEBUG=-g

build:	libLBFGS.o tests/test_1

tests/test_1:	libLBFGS.o tests/test_1.c
	$(CC) $(LFLAGS) $(OPTIM) $(DEBUG) -o tests/test_1 tests/test_1.c libLBFGS.o

libLBFGS.o:		libLBFGS.c libLBFGS.h
	$(CC) $(CFLAGS) $(OPTIM) libLBFGS.c

clean:
	rm libLBFGS.o tests/test_1
