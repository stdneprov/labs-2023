all: main.o deq.o sort.o
	gcc -o all main.o deq.o sort.o
main.o: main.c deq.h
	gcc -c main.c
sort.o: sort.c deq.h
	gcc -c sort.c
deq.o: deq.c deq.h
	gcc -c deq.c