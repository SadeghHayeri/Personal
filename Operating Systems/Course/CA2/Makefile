all: server

server: server.cpp
	g++ server.cpp -o server

gdb:
	gcc mainserver.c mainServerCore.o utility.o linkedlist.o network.o -o mainserver -g -Wall
	gcc server.c network.c utility.o -o server -g -Wall
	gcc client.c -o client -g -Wall

clean:
	rm *.o server