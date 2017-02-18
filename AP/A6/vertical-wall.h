#ifndef _VERTICAL_WALL_H_
#define _VERTICAL_WALL_H_

#include "wall.h"
#include "utility.h"
class Wall;

class VerticalWall : public Wall {
public:
    VerticalWall( coordinate _startPoint, coordinate _endPoint ) : Wall(_startPoint, _endPoint) {};
    bool contain( Child* child );
    bool collision( Child* child );
    void reflect( Child* child, Query* myQuery );
private:
};

#endif /* _VERTICAL_WALL_H_ */
