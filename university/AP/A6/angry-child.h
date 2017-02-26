#ifndef _ANGRY_CHILD_H_
#define _ANGRY_CHILD_H_

#include "child.h"
class Child;

#define MIN_ANGRY_A 70
#define CHARISMA_A 20
#define MIN_COURAGE_A 50

class AngryChild : public Child {
public:
    AngryChild( int _id, int _radius, float _posX, float _posY, float _vX, float _vY, int _anger, int _charisma, int _courage, bool _fragile );

	void setAnger( int _anger );
	void setCharisma( int _charisma );
	void setCourage( int _courage );

    virtual string getType() { return "Angry"; }
    void checkAllCollision( vector< Child* > children, Query* myQuery );

private:

};

#endif /* _ANGRY_CHILD_H_ */
