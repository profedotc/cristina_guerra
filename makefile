CC = gcc
FLAGS = -Wall -Wextra

.PHONY: main_test

all: main main_test 

release: FLAGS +=-O3
release: main

debug: FLAGS += -g -O0
debug: main

test: FLAGS += -g -O3
test: main_test

main_test: main_test.o gol.o
	$(CC) $(FLAGS) main_test.o gol.o -o main_test
	valgrind --leak-check=full ./main_test

main_test.o: main_test.c gol.o
	$(CC) $(FLAGS) -c main_test.c

main: main.o gol.o
	$(CC) $(FLAGS) main.o gol.o -o main

main.o: main.c gol.h
	$(CC) $(FLAGS) -c main.c

gol.o: gol.c gol.h
	$(CC) $(FLAGS) -c gol.c

clean:
	rm *.o main
