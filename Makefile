CC = gcc
CFLAGS ?= -std=c99 -Wall -Wextra -pedantic -O2

.PHONY: all clean

all: algorithm_explorer

algorithm_explorer: main.c datastructures.c sorting.c datastructures.h sorting.h
	$(CC) $(CFLAGS) -o $@ main.c datastructures.c sorting.c

clean:
	$(RM) algorithm_explorer algorithm_explorer.exe
