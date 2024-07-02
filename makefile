# Makefile
CC = gcc
CFLAGS = -Wall -g
DEPS = cliente.h tabela_hash.h
OBJ = main.o cliente.o tabela_hash.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o main