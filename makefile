all: lib m
	
m:	
	gcc main.c ./mylib.a -o output/solution

lib: stack stack_module stack_item
	ar r ./mylib.a ./*.o
	rm ./*.o

stack:
	gcc -c ./stack.c -o ./stack.o

stack_module:
	gcc -c ./stack_module.c -o ./stack_module.o

stack_item:
	gcc -c ./stack_item.c -o ./stack_item.o

o:
	output/sol*
c:
	rm output/*
	rm mylib.a