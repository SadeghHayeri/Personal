#include "coward-child.h"
#include "query.h"
#include "set-attribute-cmd.h"

CowardChild::CowardChild( int _id, int _radius, float _posX, float _posY, float _vX, float _vY, int _anger, int _charisma, int _courage, bool _fragile )
    : Child( _id, _radius, _posX, _posY, _vX, _vY, _anger, _charisma, _courage, _fragile ) {
    setAnger(_anger);
    setCharisma(_charisma);
    setCourage(_courage);
}


void CowardChild::setAnger( int _anger ) {
    anger = ( _anger < MIN_ANGRY_C ) ? MIN_ANGRY_C : _anger;
}

void CowardChild::setCharisma( int _charisma ) {
    charisma = CHARISMA_C;
}

void CowardChild::setCourage( int _courage ) {
    courage = COURAGE_C;
}

void CowardChild::checkAllCollision( vector< Child* > children, Query* myQuery ) {
    for (size_t i = 0; i < children.size(); i++) {
        if( collision(children[i]) ) {

            checkForBreak(this, children[i], myQuery);

            // +5 anger every collision
            int deltaAnger = +5;
            int deltaCharisma = 0;
            int deltaCourage = 0;
            myQuery->addCmd( new SetAtterCmd(this, deltaAnger, deltaCharisma, deltaCourage) );

            // normal collision
            normalCollision( children[i], myQuery );

            // special collision
            if( children[i]->getAnger() > 70 ) {
                die();
            }

        }
    }
}
