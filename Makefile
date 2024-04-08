CC=gcc -g -std=c99 -pedantic -Wall

lab26: main.o queue.o
	gcc -o lab26 main.o queue.o

main.o: main.c queue.h
	gcc -c main.c

queue.o: queue.c queue.h
	gcc -c queue.c

clean: 
	rm -rf main.o queue.o