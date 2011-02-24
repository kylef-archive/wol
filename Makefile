
OS=$(shell uname)

ifeq ($(OS), SunOS)
	LIB = -lsocket -lnsl
endif

all:
	mkdir -p bin
	$(CC) -c wol/wol.c -o wol.o
	$(CC) -c wol/main.c -o main.o
	$(CC) $(LIBS) -o bin/wol wol.o main.o

clean:
	rm -rf *.a *.o bin
