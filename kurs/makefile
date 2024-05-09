CC = clang
CFLAGS = -std=gnu99 -pedantic -Wall -Wextra -Werror
TARGET = main.out

.PHONY: clean run build

build: ${TARGET}

run: build
	./${TARGET}

${TARGET}: main.o videos.o
	${CC} -o $@ $^

main.o: main.c videos.h
	${CC} ${CFLAGS} -c -o $@ $<

videos.o: videos.c videos.h
	${CC} ${CFLAGS} -c -o $@ $<

clean:
	@rm -f ./*.o
	@rm -f ${TARGET}