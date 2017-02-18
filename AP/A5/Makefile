make: pj clean

pj: main.o row.o matrix.o
	g++ main.o row.o matrix.o

main.o: main.cpp row.cpp matrix.cpp matrix.h row.h
	g++ -c main.cpp

matrix.o: row.cpp matrix.cpp matrix.h row.h
	g++ -c matrix.cpp

row.o: row.cpp matrix.cpp matrix.h row.h
	g++ -c row.cpp

clean:
	rm *.o -f

run:
	./A5./A5./A5
# touch filename
