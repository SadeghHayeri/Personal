all: main

main: network.o main.cpp
	g++ main.cpp network.o layer.o node.o -pthread -std=c++11

network.o: network.cpp network.h layer.o
	g++ network.cpp -c -pthread -std=c++11

layer.o: layer.cpp layer.h node.o
	g++ layer.cpp -c -pthread -std=c++11

node.o: node.cpp node.h
	g++ node.cpp -c -pthread -std=c++11

clean:
	rm *.o main out
