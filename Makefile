
OS=$(shell uname)

ifeq ($(OS), SunOS)
	LIB = -lsocket -lnsl
endif

all:
	mkdir -p bin
	$(CC) -c wol/main.c -o wol.o
	$(CC) $(LIBS) -o bin/wol wol.o

clean:
	rm -rf *.a *.o bin
