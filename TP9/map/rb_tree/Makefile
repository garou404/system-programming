CC=gcc
DEPS=map_tree.h

%.o:%.c  $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_tree: test_tree.o map_tree.o
	$(CC) -o test_tree test_tree.o map_tree.o

.PHONY: clean

clean:
	rm -f *.o

