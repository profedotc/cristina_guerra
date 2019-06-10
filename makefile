CC = gcc
FLAGS = -O3
all:main 

release: main

debug: FLAGS = -g -O0
debug: main

main: main.o gol.o
	$(CC) $(FLAGS) main.o gol.o -o main

main.o: main.c gol.h
	$(CC) -c main.c

gol.o: gol.c gol.h
	$(CC) -c gol.c

clean:
	rm *.o main
