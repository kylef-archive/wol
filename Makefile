
AR = ar
ARFLAGS = rcs
LIBS = -Llib -lwol

OS=$(shell uname)

ifeq ($(OS), SunOS)
	LIB = -lsocket -lnsl
endif

all: library
	mkdir -p bin
	$(CC) -c wol/main.c -o main.o
	$(CC) $(LIBS) -o bin/wol main.o

library:
	mkdir -p lib
	$(CC) -c wol/wol.c -o wol.o -DLIBRARY
	$(AR) $(ARFLAGS) lib/libwol.a wol.o

clean:
	rm -rf *.a *.o bin lib
