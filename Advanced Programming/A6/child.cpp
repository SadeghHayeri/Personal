#include "child.h"
#include "query.h"
#include "break-cmd.h"
#include "set-attribute-cmd.h"

Child::Child( int _id, int _radius, float _posX, float _posY, float _vX, float _vY, int _anger, int _charisma, int _courage, bool _fragile ) {

    id = _id;
    radius = _radius;

    position.x = _posX;
    position.y = _posY;

    speed.x = _vX;
    speed.y = _vY;

    fragile = _fragile;
    alive = true;

}

void Child::move( int dt ) {
    position.x += speed.x * dt;
    position.y += speed.y * dt;
}

bool Child::collision( Child* child ) {
    if( child == this )
        return false;
    return ( getDistance( this->position, child->position) <= this->radius + child->radius );
}

void Child::normalCollision( Child* child, Query* myQuery ) {
    speedElements deltaSpeed;
    deltaSpeed.x = ( ( pow(radius,2) - pow(child->radius,2) ) / ( pow(radius,2) + pow(child->radius, 2) ) ) * speed.x + ( (2*pow(child->radius,2)) / (pow(radius,2) + pow(child->radius,2) ) ) * child->speed.x;
    deltaSpeed.y = ( ( pow(radius,2) - pow(child->radius,2) ) / ( pow(radius,2) + pow(child->radius, 2) ) ) * speed.y + ( (2*pow(child->radius,2)) / (pow(radius,2) + pow(child->radius,2) ) ) * child->speed.y;
    myQuery->addCmd( new SetAtterCmd(this, deltaSpeed) );
}

void Child::checkForBreak( Child* a, Child* b, Query* myQuery ) {
    if( a->radius < 6 )
        die();
    else if( a->radius + b->radius > 20 )
        if( a->checkFragile() )
            myQuery->addCmd( new BreakCmd(a) );
}
