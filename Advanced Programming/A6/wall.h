#ifndef _WALL_H_
#define _WALL_H_

#include "child.h"
#include "utility.h"
#include "query.h"

#define BLOCKSIZE 1

class Wall {
public:

    Wall( coordinate _startPoint, coordinate _endPoint ) : startPoint(_startPoint), endPoint(_endPoint) {};
    virtual void reflect( Child* child, Query* myQuery ) = 0;
    //virtual bool collision( Child* child ) = 0;
    virtual bool contain( Child* child ) = 0;

protected:
    coordinate startPoint, endPoint;
};

#endif /* _WALL_H_ */
