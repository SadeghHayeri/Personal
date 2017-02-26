#ifndef _HORIZONTAL_WALL_H_
#define _HORIZONTAL_WALL_H_

#include "wall.h"
#include "utility.h"
class Wall;

class HorizontalWall : public Wall  {
public:
    HorizontalWall( coordinate _startPoint, coordinate _endPoint ) : Wall(_startPoint, _endPoint) {};
    bool contain( Child* child );
    bool collision( Child* child );
    void reflect( Child* child, Query* myQuery );
private:
};

#endif /* _HORIZONTAL_WALL_H_ */
