CFLAGS = -std=gnu99 -pedantic -Wall -Wextra -Werror
TARGET = main.out

.PHONY: clean run build

build: ${TARGET}

run: build
	./${TARGET}

${TARGET}: main.o list.o
	${CC} -o $@ $^

main.o: main.c list.h
	${CC} ${CFLAGS} -c -o $@ $<

list.o: list.c list.h
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	@rm -f ./*.o
	@rm -f ${TARGET}