CC = gcc

CFLAGS = -g -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -DDEBUG


all: float

integers: float.o
	gcc -o float float.o
	 
integers.o: integers.c
	gcc $(CFLAGS) ${EXTRA_CFLAGS} ${INCD} -c float.c

clean:
	rm -fr aloat

.PHONY: all test

