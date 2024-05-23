all: lib m
	
m:	
	gcc main.c ./mylib.a -o output/solution

lib: table
	ar r ./mylib.a ./*.o
	rm ./*.o

table:
	gcc -c ./table.c -o ./table.o

o:
	output/sol*
c:
	rm output/*
	rm mylib.a
