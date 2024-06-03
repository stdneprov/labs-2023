kp: kp9.o slovar.o sort.o
	gcc -o kp kp9.o slovar.o sort.o
kp9.o: kp9.c slovar.h
	gcc -c kp9.c
sort.o: sort.c slovar.h
	gcc -c sort.c
slovar.o: slovar.c slovar.h
	gcc -c slovar.c