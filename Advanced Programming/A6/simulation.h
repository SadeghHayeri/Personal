#ifndef _SIMULATION_H_
#define _SIMULATION_H_

#include <vector>
#include <exception>
#include <sstream>
#include <algorithm>
#include <stdlib.h>

#include "utility.h"
#include "map.h"
#include "child.h"
#include "angry-child.h"
#include "peaceful-child.h"
#include "coward-child.h"
#include "query.h"

using namespace std;

class Simulation {
public:
    Simulation( Map* _map, int _dt, int _T );
    void getChildsFromInput();
    void addChild( Child* newChild );
    void start();
    void printResult();
    void checkHits();
    void moveAll( int dt );
    void remove( Child* child );
    int getMaxId() { return maxId; }
    void removeDeadChilds();
private:
    int dt, T, upTime, maxId;
    Map* map;
    std::vector< Child* > children;
    Query myQuery;
};

#endif /* _SIMULATION_H_ */
