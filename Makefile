SRC=libLBFGS.c libLBFGS.h
CC=gcc
OPTIM=-O3
DEBUG=-g

all:	$(SRC) tests/test_1.c
		$(CC) $(OPTIM) -o tests/test_1 tests/test_1.c $(SRC)

debug:	$(SRC) tests/test_1.c
		$(CC) $(DEBUG) -o tests/test_1 tests/test_1.c $(SRC)

clean:
		rm *.o

