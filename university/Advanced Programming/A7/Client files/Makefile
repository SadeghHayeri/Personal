all: client

client: main.cpp client_socket.o client.o interface.o utility.o local_version.o tools.o repository.o local_book.o local_chapter.o
	g++ main.cpp client_socket.o client.o utility.o interface.o local_version.o tools.o repository.o local_book.o local_chapter.o -o client

client_socket.o: client_socket.cpp client_socket.h tools.h network_exception.h
	g++ -c client_socket.cpp

tools.o: tools.cpp tools.h
	g++ -c tools.cpp

repository.o: repository.cpp local_book.o
	g++ repository.cpp -c -Wall

local_book.o: local_book.cpp local_chapter.o
	g++ local_book.cpp -c -Wall

local_chapter.o: local_chapter.cpp local_version.o
	g++ local_chapter.cpp -c -Wall

local_version.o: local_version.cpp
	g++ local_version.cpp -c -Wall

client.o: client.cpp interface.cpp utility.cpp
	g++ client.cpp -c -Wall -std=c++11

interface.o: interface.cpp client.cpp
	g++ interface.cpp -c -Wall

utility.o: utility.cpp
	g++ utility.cpp -c -Wall -std=c++11

gdb:
	g++ main.cpp client_socket.cpp client.cpp utility.cpp interface.cpp local_version.cpp tools.cpp repository.cpp local_book.cpp local_chapter.cpp -g -std=c++11


clean:
	rm *.o
