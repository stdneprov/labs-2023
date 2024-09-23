lab26: main.o stack.o test.o sort.o
	gcc -o lab26 main.o stack.o test.o sort.o
main.o: main.c stack.h test.h sort.h
	gcc -c main.c
test.o: test.c test.h stack.h sort.h
	gcc -c test.c
sort.o: sort.c sort.h stack.h
	gcc -c sort.c
stack.o: stack.c stack.h
	gcc -c stack.c


