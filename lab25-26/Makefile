all: main
main: main.o lab26.o
	gcc main.o lab26.o -o main

main.o: main.c
	gcc main.c -c -o main.o

lab26.o: lab26.c
	gcc lab26.c -c -o lab26.o

clean:
	rm main *.o