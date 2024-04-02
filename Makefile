lab24: lab24.o queue.o stack.o item.o tree.o
	gcc -o lab24 lab24.o queue.o stack.o item.o tree.o -lm
lab24.o: lab24.c item.h queue.h stack.h tree.h
	gcc -c lab24.c
queue.o: queue.c queue.h item.h
	gcc -c queue.c
stack.o: stack.c stack.h item.h
	gcc -c stack.c
tree.o: tree.c tree.h item.h
	gcc -c tree.c
item.o: item.c item.h
	gcc -c item.c