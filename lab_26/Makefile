CC=gcc

CCFLAGS=-Wall -pedantic -std=c99

RES=lab26
OBJECT_FILES=main.o list.o

build: $(RES)

$(RES): $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) -o $(RES)

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@

main.o: list.h

list.o: list.h

clean:
	rm $(RES) $(OBJECT_FILES)