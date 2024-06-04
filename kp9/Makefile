CC = gcc
CFLAGS = -Wall -pedantic -std=c99

all: main

main: main.o table.o
	$(CC) $(CFLAGS) -o main main.o table.o

main.o: main.c table.h
	$(CC) $(CFLAGS) -c main.c

litablest.o: table.c table.h
	$(CC) $(CFLAGS) -c table.c
