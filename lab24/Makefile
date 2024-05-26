CC = gcc
CFLAGS = -Wall -pedantic -std=c99

all: main

main: main.o stack.o tree.o
	$(CC) $(CFLAGS) -o main main.o stack.o tree.o

main.o: main.c tree.h
	$(CC) $(CFLAGS) -c main.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c
