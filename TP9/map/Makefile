CC=gcc
DEPS=map_tree.h

%.o:%.c  $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# test_map: test_map.o map.o
# 	$(CC) -o test_map test_map.o map.o

test_map_tree: test_map.o map_tree.o
	$(CC) -o test_map_tree test_map.o map_tree.o

.PHONY: clean

clean:
	rm -f *.o

