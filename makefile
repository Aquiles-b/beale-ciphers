CC=gcc
CFLAGS= -g -Wall -std=c99

OBJS= decodifica_lib.o cifrasBeale_lib.o lista_lib.o files_lib.o

beale: $(OBJS) beale.c
	$(CC) beale.c -o beale $(OBJS) $(CFLAGS)

decod: $(OBJS)
	$(CC) -o decod $(OBJS) $(CFLAGS)

%_lib.o: %_lib.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *_lib.o beale
