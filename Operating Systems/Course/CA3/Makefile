all: main

main: network.o main.cpp
	g++ main.cpp network.o -o main -std=c++11

network.o: network.cpp network.h
	g++ network.cpp -c -std=c++11

layer.o: layer.cpp layer.h
	g++ layer.cpp -c -std=c++11

node.o: node.cpp node.h
	g++ node.cpp -c -std=c++11

clean:
	rm *.o main
