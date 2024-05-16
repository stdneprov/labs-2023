lab26: main.o queue.o sort.o
	gcc -o lab26 main.o queue.o sort.o
main.o: main.c queue.h
	gcc -c main.c
sort.o: sort.c queue.h
	gcc -c sort.c
queue.o: queue.c queue.h
	gcc -c queue.c