#ifndef _CHILD_H_
#define _CHILD_H_

#include <vector>
#include "utility.h"
#include "child.h"
#include "query.h"

using namespace std;

class Child {
public:

	Child( int _id, int _radius, float _posX, float _posY, float _vX, float _vY, int _anger, int _charisma, int _courage, bool _fragile );
	void move( int dt );

	void setSpeed( speedElements _speed ) { speed = _speed; }
	virtual void setRadius( int _radius ) { radius = _radius; }
	virtual void setAnger( int _anger ) = 0;
	virtual void setCharisma( int _charisma ) = 0;
	virtual void setCourage( int _courage ) = 0;

	int getId() { return id; }
	int getRadius() { return radius; }
	virtual string getType() = 0;
	coordinate getPosition() { return position; }
	speedElements getSpeed() { return speed; }
	int getAnger() { return anger; }
	int getCharisma() { return charisma; }
	int getCourage() { return courage; }
	bool checkLife() { return alive; }
	bool checkFragile() { return fragile; }

	bool collision( Child* child );
	void checkForBreak( Child* a, Child* b, Query* myQuery );
	void normalCollision( Child* child, Query* myQuery );
	virtual void checkAllCollision( vector< Child* > children, Query* myQuery ) = 0;
	void die() { alive = false; }

protected:

	int anger;
	int charisma;
	int courage;
	int radius;

private:

    int id;

    coordinate position;
    speedElements speed;

    bool fragile;
	bool alive;

};

#endif /* _CHILD_H_ */
