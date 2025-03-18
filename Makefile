CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LIBS = -lcunit

SRC = src/matrix.c
TESTS = tests/test_matrix.c
OBJ = $(SRC:.c=.o)
EXEC = bin/matrix_test

all: test

test: $(SRC) $(TESTS)
	mkdir -p bin
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC) $(TESTS) $(LIBS)
	./$(EXEC)

clean:
	rm -rf bin *.o
