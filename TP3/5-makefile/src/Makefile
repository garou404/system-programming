CC=gcc
DEPS=foo.h
CFLAGS=-Wall -Werror

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)



main: main.o foo.o
	$(CC) -o main main.o foo.o -L../libtab/ -lmemory


main: make_lib

make_lib:
	make -C ../libtab/

.PHONY: clean clean_o

clean_o:
	rm -f *.o

clean:
	rm -f *.o main