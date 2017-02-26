all: server

server: main.cpp server_socket.o server.o myserver.o tools.o user.o book.o utility.o version.o chapter.o database.o user_list.o
	g++ main.cpp server_socket.o server.o tools.o myserver.o user.o book.o utility.o version.o chapter.o database.o user_list.o -o server

server.o: server.cpp server.h
	g++ -c server.cpp

server_socket.o: server_socket.cpp server_socket.h tools.h network_exception.h
	g++ -c server_socket.cpp

tools.o: tools.cpp tools.h
	g++ -c tools.cpp

myserver.o: myserver.cpp database.cpp utility.cpp user_list.cpp
	g++ myserver.cpp -c -Wall

user_list.o: user_list.cpp myserver.cpp
	g++ user_list.cpp -c -Wall

database.o: myserver.cpp database.cpp book.cpp utility.cpp
	g++ database.cpp -c -Wall

user.o: user.cpp utility.cpp
	g++ user.cpp -c -Wall

book.o: book.cpp chapter.cpp utility.cpp
	g++ book.cpp -c -Wall

chapter.o: chapter.cpp version.cpp utility.cpp
	g++ chapter.cpp -c -Wall

version.o: version.cpp utility.cpp
	g++ version.cpp -c -Wall

utility.o: utility.cpp
	g++ utility.cpp -c -Wall -std=c++11

clean:
	rm *.o
