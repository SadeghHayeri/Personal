make: simulation

simulation: main.o simulation.o child.o angry-child.o peaceful-child.o coward-child.o map.o wall.o horizontal-wall.o vertical-wall.o query.o command.o break-cmd.o reflect-cmd.o set-attribute-cmd.o alliance-cmd.o utility.o
	g++ main.o simulation.o child.o angry-child.o peaceful-child.o coward-child.o map.o wall.o horizontal-wall.o vertical-wall.o query.o command.o break-cmd.o reflect-cmd.o set-attribute-cmd.o alliance-cmd.o utility.o -o simulation

main.o: main.cpp child.o utility.o
	g++ main.cpp -c

utility.o: utility.h utility.cpp
	g++ utility.cpp -c

simulation.o: simulation.h simulation.cpp main.o utility.o
	g++ simulation.cpp -c

child.o: child.cpp child.h angry-child.o peaceful-child.o coward-child.o utility.o
	g++ child.cpp -c

angry-child.o: child.cpp child.h angry-child.cpp angry-child.h utility.o
	g++ angry-child.cpp -c

peaceful-child.o: child.cpp child.h peaceful-child.cpp peaceful-child.h utility.o
	g++ peaceful-child.cpp -c

coward-child.o: child.cpp child.h coward-child.cpp coward-child.h utility.o
	g++ coward-child.cpp -c

map.o: map.cpp map.h coward-child.o wall.o utility.o
	g++ map.cpp -c

wall.o: wall.cpp wall.h map.cpp map.h horizontal-wall.o vertical-wall.o utility.o
	g++ wall.cpp -c

horizontal-wall.o: horizontal-wall.h horizontal-wall.cpp wall.cpp wall.h utility.o
	g++ horizontal-wall.cpp -c

vertical-wall.o: vertical-wall.h vertical-wall.cpp wall.cpp wall.h utility.o
	g++ vertical-wall.cpp -c

query.o: query.h query.cpp main.o child.o command.cpp command.h
	g++ query.cpp -c

command.o: command.h command.cpp query.o break-cmd.cpp set-attribute-cmd.cpp break-cmd.h set-attribute-cmd.h alliance-cmd.h alliance-cmd.cpp reflect-cmd.cpp reflect-cmd.h
	g++ command.cpp -c

break-cmd.o: break-cmd.h break-cmd.cpp command.o
	g++ break-cmd.cpp -c

reflect-cmd.o: reflect-cmd.h reflect-cmd.cpp command.o
	g++ reflect-cmd.cpp -c

set-attribute-cmd.o: set-attribute-cmd.h set-attribute-cmd.cpp command.o
	g++ set-attribute-cmd.cpp -c

alliance-cmd.o: alliance-cmd.h alliance-cmd.cpp command.o
	g++ alliance-cmd.cpp -c


clean:
	rm *.o -f

gdb:
	g++ main.cpp simulation.cpp child.cpp angry-child.cpp peaceful-child.cpp coward-child.cpp map.cpp wall.cpp horizontal-wall.cpp vertical-wall.cpp query.cpp command.cpp break-cmd.cpp reflect-cmd.cpp set-attribute-cmd.cpp alliance-cmd.cpp utility.cpp -o simulation -g

wall:
	g++ main.cpp simulation.cpp child.cpp angry-child.cpp peaceful-child.cpp coward-child.cpp map.cpp wall.cpp horizontal-wall.cpp vertical-wall.cpp query.cpp command.cpp break-cmd.cpp reflect-cmd.cpp set-attribute-cmd.cpp alliance-cmd.cpp utility.cpp -o simulation -Wall

run:
	./A6
# touch filename
