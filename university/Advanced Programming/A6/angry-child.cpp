#include "angry-child.h"
#include "query.h"
#include "set-attribute-cmd.h"

AngryChild::AngryChild( int _id, int _radius, float _posX, float _posY, float _vX, float _vY, int _anger, int _charisma, int _courage, bool _fragile )
    : Child( _id, _radius, _posX, _posY, _vX, _vY, _anger, _charisma, _courage, _fragile ) {
    setAnger(_anger);
    setCharisma(_charisma);
    setCourage(_courage);
}


void AngryChild::setAnger( int _anger ) {
    anger = ( _anger < MIN_ANGRY_A ) ? MIN_ANGRY_A : _anger;
}

void AngryChild::setCharisma( int _charisma ) {
    charisma = CHARISMA_A;
}

void AngryChild::setCourage( int _courage ) {
    courage = ( _courage < MIN_COURAGE_A ) ? MIN_COURAGE_A : _courage;
}

void AngryChild::checkAllCollision( vector< Child* > children, Query* myQuery ) {
    for (size_t i = 0; i < children.size(); i++) {
        if( collision(children[i]) ) {

            checkForBreak(this, children[i], myQuery);

            // normal collision
            normalCollision( children[i], myQuery );

            // special collision
            if( children[i]->getAnger() > 70 ) {
                if(radius < children[i]->getRadius()) {
                    int deltaRadius = radius * -0.8;
                    int deltaAnger = +5;
                    int deltaCharisma = 0;
                    int deltaCourage = 0;
                    myQuery->addCmd( new SetAtterCmd(this, deltaRadius) );
                    myQuery->addCmd( new SetAtterCmd(this, deltaAnger, deltaCharisma, deltaCourage) );
                }
            } else if( children[i]->getCourage() > 30 && children[i]->getCharisma() > 50 ) {
                int deltaRadius = +(1-((courage+charisma)/200)) * 0.8 * radius;
                myQuery->addCmd( new SetAtterCmd(this, deltaRadius) );
            }

        }
    }
}
