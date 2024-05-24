CC = clang
CFLAGS = -std=gnu99 -pedantic -Wall -Wextra -Werror
TARGET = main.out

.PHONY: clean run build

build: ${TARGET}

run: build
	./${TARGET}

${TARGET}: main.o table.o
	${CC} -o $@ $^

main.o: main.c table.h
	${CC} ${CFLAGS} -c -o $@ $<

list.o: table.c table.h
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	@rm -f ./*.o
	@rm -f ${TARGET}