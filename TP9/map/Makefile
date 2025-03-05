CC=gcc
DEPS=map.h

%.o:%.c  $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_map: test_map.o map.o
	$(CC) -o test_map test_map.o map.o

.PHONY: clean

clean:
	rm -f *.o

