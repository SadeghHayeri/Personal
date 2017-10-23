all: mainServer server

test: *
	rm test
	gcc test.c linkedlist.c -o test
	./test

mainServer: mainserver.c mainServerCore linkedlist utility network
	gcc mainserver.c mainServerCore.o utility.o linkedlist.o network.o -o mainserver

mainServerCore: mainServerCore.c mainServerCore.h
	gcc mainServerCore.c -c

linkedlist: linkedlist.c linkedlist.h
	gcc linkedlist.c -c

utility: utility.c utility.h
	gcc utility.c -c

network: network.c network.h
	gcc network.c -c

server: server.c
	gcc server.c network.c -o server

client: client.c
	gcc client.c -o client

gdb:
	gcc mainserver.c -o mainserver -g -Wall
	gcc server.c -o server -g -Wall
	gcc client.c -o client -g -Wall

clean:
	rm mainserver server client linkedlist.o utility.o network.o mainServerCore.o a.out
