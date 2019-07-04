CC = gcc
FLAGS = -Wall -Wextra

.PHONY: all release debug test clean

all: main

release: FLAGS +=-O3
release: main

debug: FLAGS += -g -O0
debug: main

test: main_test
	valgrind --leak-check=full ./main_test

main_test: FLAGS += -g -O3
main_test: main_test.o gol.o
	$(CC) $(FLAGS) main_test.o gol.o -o main_test

main_test.o: main_test.c gol.h
	$(CC) $(FLAGS) -c main_test.c

main: main.o gol.o
	$(CC) $(FLAGS) main.o gol.o -o main

main.o: main.c gol.h
	$(CC) $(FLAGS) -c main.c

gol.o: gol.c gol.h
	$(CC) $(FLAGS) -c gol.c

clean:
	rm -f *.o main main_test
