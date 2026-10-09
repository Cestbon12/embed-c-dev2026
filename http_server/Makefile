CC = gcc
CFLAGS = -Wall -Wextra -g

all: server client http_server

server: server.c
	$(CC) $(CFLAGS) -o $@ $<

client: client.c
	$(CC) $(CFLAGS) -o $@ $<

http_server: http_server.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f server client http_server
