all: lib m
	
m:	
	gcc main.c ./mylib.a -o output/solution

lib: stack tree
	ar r ./mylib.a ./*.o
	rm ./*.o
	
tree:
	gcc -c ./tree.c -o ./tree.o
stack:
	gcc -c ./stack.c -o ./stack.o

o:
	output/sol*
c:
	rm output/*
	rm mylib.a
	