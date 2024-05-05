CC=gcc -g -Wall -std=c99 -pedantic
all: main
default: main
main: main.o stack.o sort.o
	gcc main.o stack.o sort.o

stack.o: stack.c stack.h
	gcc stack.c -c -o stack.o

sort.o: sort.c sort.h
	gcc sort.c -c -o sort.o

clean: 
	rm -rf main.o