main: main.o list.o 
        gcc -o main main.o list.o 
main.o: main.c list.h
        gcc -c main.c
list.o: list.c list.h
        gcc -c list.c

  