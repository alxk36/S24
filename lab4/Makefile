CC = gcc
CFLAGS = -g -Wall -Wextra
FILES = main.c alloc.c mult.c print.c read.c


COMPILED_FILE = program.exe

all.o = main.o alloc.o mult.o print.o read.o
all:
	$(CC) $(FILES) -o ${COMPILED_FILE} $(CFLAGS) 

clean:
	rm ${COMPILED_FILE} ${all.o}