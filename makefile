CC=gcc
CFLAGS= -g -Wall -std=c99

lista: lista.c
	$(CC) lista.c -o lista $(CFLAGS)

run: lista
	./lista

clean:
	rm -f lista
