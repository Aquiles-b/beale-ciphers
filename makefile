CC=gcc
CFLAGS= -Wall -std=c99

OBJS= beale.o decodifica_lib.o codifica_lib.o cifrasBeale_lib.o lista_lib.o

all: beale

beale: $(OBJS)
	$(CC) -o beale $(OBJS) $(CFLAGS)

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f $(OBJS)

purge:
	rm -f $(OBJS) beale
