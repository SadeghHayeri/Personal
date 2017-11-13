all: server client

server: server.cpp utility.o pipe.o network.o p1.h p2.h
	g++ server.cpp utility.o pipe.o network.o -o server -std=c++11

client: client.cpp network.o
	g++ client.cpp network.o -o client -std=c++11

utility.o: utility.h utility.cpp
	g++ utility.cpp -c -std=c++11

pipe.o: pipe.h pipe.cpp
	g++ pipe.cpp -c -std=c++11

network.o: network.h network.cpp
	g++ network.cpp -c -std=c++11

clean:
	rm *.o server client
