all: read write


read: read.o db.o
	gcc read.o db.o -o read

write: write.o db.o
	gcc write.o db.o -o write

read.o: read_from_db.c
	gcc read_from_db.c -c -o read.o

write.o: write_from_db.c
	gcc write_from_db.c -c -o write.o

db.o: db.c
	gcc db.c -c -o db.o