CC=gcc

CCFLAGS=-Wall -pedantic -std=c99

RES=KP_9
OBJECT_FILES=kp9.o sort.o table.o

build: $(RES)

$(RES): $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) -o $(RES)

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@

kp9.o: table.h

sort.o: table.h

table.o: table.h

clean:
	rm $(RES) $(OBJECT_FILES)