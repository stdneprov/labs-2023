prog: main.o queue.o bubble_sort.o
	gcc -o prog main.o queue.o bubble_sort.o

main.o: main.c queue.h bubble_sort.h
	gcc -c main.c

queue.o: queue.c queue.h
	gcc -c queue.c

bubble_sort.o: bubble_sort.c bubble_sort.h queue.h
	gcc -c bubble_sort.c