CC=gcc
CFLAGS= -g -Wall -std=c99

OBJS= lista_lib.o

beale: $(OBJS) beale.c
	$(CC) beale.c -o beale $(OBJS) $(CFLAGS)

decod: decodifica_lib.o 
	$(CC) -o decod decodifica_lib.o $(CFLAGS)

%_lib.o: %_lib.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *_lib.o beale
