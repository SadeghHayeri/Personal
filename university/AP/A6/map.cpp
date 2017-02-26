#include "map.h"
#include "wall.h"
#include "horizontal-wall.h"
#include "vertical-wall.h"

void Map::makeWall( wallType type, int startX, int startY, int endX, int endY ) {

    coordinate start, end;
    start.x = startX;
    start.y = startY;
    end.x = endX;
    end.y = endY;

    Wall* newWall;
    if( type == horizontal )
        newWall = new HorizontalWall( start, end );
    else
        newWall = new VerticalWall( start, end );
    walls.push_back( newWall );
}

Map::Map( std::string fileName ) {

    // open map
    std::ifstream file( "map.dat" );
    if( !file ) {
        throw std::invalid_argument( "invalid matrix!" );
    }

    // read map to mapFile
    std::vector< std::string > mapFile;
    int length;
    file >> length;
    std::string line;
    while( file >> line )
        mapFile.push_back(line);

    int size = mapFile.size();

    // find horizontal-wall
    for (size_t i = 0; i < size; i++) {
        int start = 0;
        int end = 0;
        for (size_t j = 0; j < size; j++) {

            if( mapFile[i][j] == 'b' ) {
                end = j;
            } else {
                if( start != end ) {
                    makeWall( horizontal, start, i, end, i );
                }
                start = j+1;
                end = j+1;
            }

        }
    }

    // find vertical-wall
    for (size_t i = 0; i < size; i++) {
        int start = 0;
        int end = 0;
        for (size_t j = 0; j < size; j++) {

            if( mapFile[j][i] == 'b' ) {
                end = j;
            } else {
                if( start != end ) {
                    makeWall( vertical, i, start, i, end );
                }
                start = j+1;
                end = j+1;
            }

        }
        if( start != end ) {
            makeWall( vertical, i, start, i, end );
        }
    }

    // free mapFile
    size = mapFile.size();
    mapFile.clear();

}

bool Map::contain( Child* child ) {
    for (size_t i = 0; i < walls.size(); i++) {
        if( walls[i]->contain(child) )
            return true;
    }
    return false;
}

void Map::reflect( Child* child, Query* myQuery ) {

    if( contain(child) || child->getPosition().x + BLOCKSIZE > size || child->getPosition().y > size + BLOCKSIZE )
        child->die();
    else
        for (size_t i = 0; i < walls.size(); i++)
            walls[i]->reflect( child, myQuery );

}
