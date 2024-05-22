all: delete lib m
	./src/main/main.o
m:	
	gcc main.c ./src/list/list.o -o ./src/main/main.o

lib: 
	gcc -c list.c -o ./src/list/list.o

run:
	./src/main/main.o
	
delete: 
	rm -f ./src/list/list.o
	rm -f ./src/main/main.o
