CC = gcc
CFLAGS = -02

all:
	mkdir -p bin
	$(CC) -c wol/main.c -o wol.o
	$(CC) -o bin/wol wol.o

clean:
	rm -rf *.a *.o bin
