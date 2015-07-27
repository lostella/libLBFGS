SRC=libLBFGS.c
TESTS=test1
CC=gcc

all:	$(TESTS)

test1:	$(SRC) test_1.c
		$(CC) -o test_1 test_1.c $(SRC)

clean:
		rm *.o

