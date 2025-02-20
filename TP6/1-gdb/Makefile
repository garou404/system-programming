BIN=list
CFLAGS=-O0
LDFLAGS=

all: $(BIN)

list: list.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -g
clean:
	rm -f $(BIN)
