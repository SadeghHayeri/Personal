all: server

server: server.cpp utility.o pipe.o
	g++ server.cpp utility.o pipe.o -std=c++11

utility.o: utility.h utility.cpp
	g++ utility.cpp -c -std=c++11

pipe.o: pipe.h pipe.cpp
	g++ pipe.cpp -c -std=c++11

clean:
	rm *.o server