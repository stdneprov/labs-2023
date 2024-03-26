CC=gcc -g -Wall -std=99c -pedantic
all: main
default: main
main: main.o tree.o stack.o
	gcc main.o tree.o stack.o

main.o: main.c tree.h
	gcc main.c -c -o main.o 

tree.o: tree.c tree.h
	gcc tree.c -c -o tree.o

stack.o: stack.c stack.h
	gcc stack.c -c -o stack.o

clean: 
	rm -rf main.o tree.o
