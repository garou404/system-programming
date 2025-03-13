CC=gcc
FLAGS=-Wall -Werror
OBJS_ser=server.o server_code_etudiant.o
OBJS_cli=client.o client_code_etudiant.o


%.o: %.c
	$(CC) -o $@ -c $< $(FLAGS)

server: $(OBJS_ser)
	$(CC) -o $@ $^ 

client: $(OBJS_cli)
	$(CC) -o $@ $^

clean:
	rm -f client server *.o