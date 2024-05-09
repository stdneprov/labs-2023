main: main.o stack.o tree.o
  gcc -o main main.o stack.o tree.o
main.o: main.c stack.h tree.h
  gcc -c main.c
stack.o: stack.c stack.h
  gcc -c stack.c
tree.o: tree.c tree.h stack.h
  gcc -c tree.c
  