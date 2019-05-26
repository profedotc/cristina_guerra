all:main

main all clean: gol.o gol.h
	gcc gol.o -o main

gol.o: gol.c
	gcc -c gol.c
