CC = gcc
CFLAGS = -Wall -Werror -Wfatal-errors -pedantic

all: list.c
	$(CC) -c list.c $(CFLAGS)
  
test: list.c main.c
	$(CC) main.c list.c $(CFLAGS) -o test
  
clean:
	-rm list.o
	-rm test
