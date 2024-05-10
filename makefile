all: lib m
	
m:	
	mkdir output
	gcc main.c ./mylib.a -o output/solution
	gcc convert_to_binary.c -o output/convert
	./output/convert data.bin data.txt

lib: string
	ar r ./mylib.a ./*.o
	rm ./*.o
	
string:
	gcc -c ./mystring.c -o ./mystring.o

conv:
	./output/convert data.bin data.txt

o:
	output/sol* data.bin -p

of:
	output/sol* data.bin -f

c:
	rm -rf output
	rm mylib.a
	rm data.bin
	