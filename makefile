CC=gcc
CFLAGS= -g -Wall -std=c99

OBJS= decodifica_lib.o cifrasBeale_lib.o lista_lib.o files_lib.o

beale: $(OBJS) beale.c
	$(CC) beale.c -o beale $(OBJS) $(CFLAGS)

decod: $(OBJS)
	$(CC) -o decod $(OBJS) $(CFLAGS)

cifras: cifrasBeale_lib.o lista_lib.o
	$(CC) -o cifras cifrasBeale_lib.o lista_lib.o

run: cifras
	./cifras

%_lib.o: %_lib.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *_lib.o beale cifras
