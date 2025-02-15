CC=gcc
DEPS=tab.h
CFLAGS=-fPIC

%.o:%.c  $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

libmemory.so: tab.o
	$(CC) -shared -o libmemory.so tab.o

.PHONY: clean_o

clean_o:
	rm -f *.o

