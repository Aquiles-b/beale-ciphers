CC=gcc
CFLAGS= -g -Wall -std=c99

OBJS= lista.o

beale: $(OBJS) beale.c
	$(CC) beale.c -o beale $(OBJS) $(CFLAGS)

lista.o: lista.c
	$(CC) -c lista.c $(CFLAGS)

clean:
	rm -f $(OBJS) beale
