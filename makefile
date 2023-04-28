CC=gcc
CFLAGS= -g -Wall -std=c99

OBJS= beale.o decodifica_lib.o codifica_lib.o cifrasBeale_lib.o lista_lib.o

beale: $(OBJS)
	$(CC) -o beale $(OBJS) $(CFLAGS)

run: beale
	./beale

%_lib.o: %_lib.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f $(OBJS) beale
