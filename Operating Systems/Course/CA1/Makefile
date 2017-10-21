all: mainserver server client

test: *
	rm test
	gcc test.c linkedlist.c -o test
	./test

mainserver: mainserver.c linkedlist.c
	gcc mainserver.c linkedlist.c -o mainserver
	./mainserver

server: server.c
	gcc server.c -o server

client: client.c
	gcc client.c -o client

gdb:
	gcc mainserver.c -o mainserver -g -Wall
	gcc server.c -o server -g -Wall
	gcc client.c -o client -g -Wall

clean:
	rm mainserver server client test
