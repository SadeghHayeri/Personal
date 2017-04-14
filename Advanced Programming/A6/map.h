#ifndef _MAP_H_
#define _MAP_H_

#include <vector>
#include <string>
#include <fstream>
#include <exception>
#include <stdexcept>

#include "query.h"
#include "child.h"
#include "wall.h"

class Child;
class Wall;
enum wallType { horizontal, vertical };

#define MAP_SIZE 10

class Map {
public:
    Map( std::string fileName );
    void reflect( Child* child, Query* myQuery );
    void makeWall( wallType type, int startX, int startY, int endX, int endY );
    bool contain( Child* child );
private:
    std::vector < Wall* > walls;
    int size;
};

#endif /* _MAP_H_ */
