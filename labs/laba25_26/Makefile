

out: main.o stack.o
	gcc -o out main.o stack.o

main.o: main.c
	gcc -c main.c

stack.o: stack.c
	gcc -c stack.c

clean: 
	rm -rf *.o out