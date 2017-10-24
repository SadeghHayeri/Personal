all: mainServer server client

test: *
	rm test
	gcc test.c linkedlist.c -o test
	./test

mainServer: mainserver.c mainServerCore linkedlist utility network
	gcc mainserver.c mainServerCore.o utility.o linkedlist.o network.o -o mainserver

server: server.c linkedlist utility network
	gcc server.c network.c utility.o -o server

client: client.c network utility
	gcc client.c network.o utility.o -o client

mainServerCore: mainServerCore.c mainServerCore.h
	gcc mainServerCore.c -c

linkedlist: linkedlist.c linkedlist.h
	gcc linkedlist.c -c

utility: utility.c utility.h
	gcc utility.c -c

network: network.c network.h
	gcc network.c -c

gdb:
	gcc mainserver.c mainServerCore.o utility.o linkedlist.o network.o -o mainserver -g -Wall
	gcc server.c network.c utility.o -o server -g -Wall
	gcc client.c -o client -g -Wall

clean:
	rm mainserver server client linkedlist.o utility.o network.o mainServerCore.o a.out r1.txt r2.txt f.txt test.txt

ctxt:
	rm r1.txt r2.txt f.txt test.txt
