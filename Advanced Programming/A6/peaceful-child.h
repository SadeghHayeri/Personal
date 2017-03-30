#ifndef _PEACEFUL_CHILD_H_
#define _PEACEFUL_CHILD_H_

#include "child.h"
class Child;

#define MAX_ANGRY_P 30
#define MIN_CHARISMA_P 50
#define MIN_COURAGE_P 30

class PeacefulChild : public Child {
public:
    
    PeacefulChild( int _id, int _radius, float _posX, float _posY, float _vX, float _vY, int _anger, int _charisma, int _courage, bool _fragile );
    void setAnger( int _anger );
    void setCharisma( int _charisma );
    void setCourage( int _courage );

    virtual string getType() { return "Peaceful"; }
    void checkAllCollision( vector< Child* > children, Query* myQuery );

private:

};

#endif /* _PEACEFUL_CHILD_H_ */
