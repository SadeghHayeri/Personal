all: server

server: server.cpp utility.o driving_fine.o date.o pipe.o
	g++ server.cpp utility.o driving_fine.o date.o pipe.o -std=c++11

utility.o: utility.h utility.cpp
	g++ utility.cpp -c -std=c++11

driving_fine.o: driving_fine.h driving_fine.cpp date.o
	g++ driving_fine.cpp -c -std=c++11

date.o: date.h date.cpp
	g++ date.cpp -c -std=c++11

pipe.o: pipe.h pipe.cpp
	g++ pipe.cpp -c -std=c++11

clean:
	rm *.o server