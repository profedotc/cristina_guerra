CC = gcc
FLAGS = -Wall -Wextra
all:main 

release: FLAGS +=-O3
release: main

debug: FLAGS += -g -O0
debug: main

main: main.o gol.o
	$(CC) $(FLAGS) main.o gol.o -o main

main.o: main.c gol.h
	$(CC) $(FLAGS) -c main.c

gol.o: gol.c gol.h
	$(CC) $(FLAGS) -c gol.c

clean:
	rm *.o main
