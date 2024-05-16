all: main

main: main.o tree.o
	gcc tree.o main.o -o main

main.o: main.c tree.h
	gcc main.c -c -o main.o

main.o: tree.c tree.h
	gcc tree.c -c -o tree.o