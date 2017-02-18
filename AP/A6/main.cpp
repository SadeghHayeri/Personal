#include <string>
#include <exception>
#include <sstream>

#include "simulation.h"
#include "map.h"
#include "utility"

using namespace std;

const string MAPNAME = "map.dat";

int main(int argc, char const *argv[]) {

    if( argc != 3)
        throw std::invalid_argument( "invalid arguments!" );

    int dt = atof( argv[1] );
    int T = atof( argv[2] );


    Map map( MAPNAME );
    Simulation simo( &map, dt, T );
    simo.getChildsFromInput();
    simo.start();

    return 0;
}
