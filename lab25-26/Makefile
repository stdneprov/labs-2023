PRC = $(wildcart *.c)
OBJ = $(patsubst *.c, *.o, $(PRC))


MyProject : $(OBJ)
	gcc $(OBJ) -o MyProject

%.o : %.c
	gcc -c $< -o $@

clean :
	rm MyProject *.o