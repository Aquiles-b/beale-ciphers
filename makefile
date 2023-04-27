CC=gcc
CFLAGS= -g -Wall -std=c99

OBJS= codifica_lib.o cifrasBeale_lib.o lista_lib.o files_lib.o

beale: $(OBJS) beale.c
	$(CC) beale.c -o beale $(OBJS) $(CFLAGS)

codi: $(OBJS)
	$(CC) -o codi $(OBJS) $(CFLAGS)

cifras: cifrasBeale_lib.o lista_lib.o
	$(CC) -o cifras cifrasBeale_lib.o lista_lib.o

run: codi
	./codi

%_lib.o: %_lib.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f *_lib.o beale cifras decod
