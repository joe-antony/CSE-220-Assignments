CC = gcc

CFLAGS = -g -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -DDEBUG


all: float

float: float.o
	gcc -o float float.o
	 
float.o: float.c
	gcc $(CFLAGS) ${EXTRA_CFLAGS} ${INCD} -c float.c

clean:
	rm -fr float.o float

.PHONY: all test

