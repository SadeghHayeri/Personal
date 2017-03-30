#ifndef _COWARD_CHILD_H_
#define _COWARD_CHILD_H_

#include "child.h"
class Child;

#define MIN_ANGRY_C 0
#define CHARISMA_C 0
#define COURAGE_C 0

class CowardChild : public Child {
public:
    CowardChild( int _id, int _radius, float _posX, float _posY, float _vX, float _vY, int _anger, int _charisma, int _courage, bool _fragile );

    void setAnger( int _anger );
    void setCharisma( int _charisma );
    void setCourage( int _courage );

    virtual string getType() { return "Coward"; }
    void checkAllCollision( vector< Child* > children, Query* myQuery );

private:

};

#endif /* _COWARD_CHILD_H_ */
