CC = clang
CFLAGS = -std=gnu99 -pedantic -Wall -Wextra -Werror
TARGET = main.out

.PHONY: clean run build

build: ${TARGET}

run: build
	./${TARGET}

${TARGET}: main.o stack.o
	${CC} -o $@ $^

main.o: main.c stack.h
	${CC} ${CFLAGS} -c -o $@ $<

stack.o: stack.c stack.h
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	@rm -f ./*.o
	@rm -f ${TARGET}