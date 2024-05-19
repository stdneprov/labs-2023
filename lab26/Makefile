CC = gcc
CFLAGS = -Wall -pedantic -std=c99

lab26: main.o list.o swap.o
	$(CC) $(CFLAGS) -o lab26 main.o list.o swap.o

main.o: main.c list.h swap.h
	$(CC) $(CFLAGS) -c main.c

swap.o: swap.c swap.h list.h
	$(CC) $(CFLAGS) -c swap.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c
