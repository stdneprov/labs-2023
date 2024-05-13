all: lib m
	
m:	
	gcc main.c ./mylib.a -o output/solution

lib: ring_list
	ar r ./mylib.a ./*.o
	rm ./*.o

ring_list:
	gcc -c ./ring_list.c -o ./ring_list.o

o:
	output/sol*
c:
	rm output/*
	rm mylib.a
