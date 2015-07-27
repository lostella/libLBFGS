SRC=libLBFGS.c
TESTS=test1
CC=gcc

all:	$(TESTS)

test1:	$(SRC) tests/test_1.c
		$(CC) -o tests/test_1 tests/test_1.c $(SRC)

clean:
		rm *.o

