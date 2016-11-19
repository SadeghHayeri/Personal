#include "peaceful-child.h"
#include "query.h"
#include "set-attribute-cmd.h"
#include "alliance-cmd.h"

PeacefulChild::PeacefulChild( int _id, int _radius, float _posX, float _posY, float _vX, float _vY, int _anger, int _charisma, int _courage, bool _fragile )
    : Child( _id, _radius, _posX, _posY, _vX, _vY, _anger, _charisma, _courage, _fragile ) {
    setAnger(_anger);
    setCharisma(_charisma);
    setCourage(_courage);
}

void PeacefulChild::setAnger( int _anger ) {
    anger = ( _anger > MAX_ANGRY_P ) ? MAX_ANGRY_P : _anger;
}

void PeacefulChild::setCharisma( int _charisma ) {
    charisma = ( _charisma < MIN_CHARISMA_P ) ? MIN_CHARISMA_P : _charisma;
}

void PeacefulChild::setCourage( int _courage ) {
    courage = ( _courage < MIN_COURAGE_P ) ? MIN_COURAGE_P : _courage;
}

void PeacefulChild::checkAllCollision( vector< Child* > children, Query* myQuery ) {

    int PeacefulCollision = 0;

    for (size_t i = 0; i < children.size(); i++) {
        if( collision(children[i]) ) {

            checkForBreak(this, children[i], myQuery);

            // special alliance for peaceful
            if( children[i]->getType() == "Peaceful" )
                PeacefulCollision++;

            // special collision
            if( children[i]->getAnger() > 70 && children[i]->getCourage() > 50 ) {

                int deltaRadius = -(1-((courage+charisma)/200)) * 0.8 * radius;
                int deltaAnger = 0;
                int deltaCharisma = 0;
                int deltaCourage = -10;
                myQuery->addCmd( new SetAtterCmd(this, deltaRadius) );
                myQuery->addCmd( new SetAtterCmd(this, deltaAnger, deltaCharisma, deltaCourage) );

            } else if( children[i]->getCourage() > 30 && children[i]->getCharisma() > 50 ) {

                int deltaAnger = 0;
                int deltaCharisma = +2;
                int deltaCourage = +2;
                myQuery->addCmd( new AllianceCmd(this, children[i]) );
                myQuery->addCmd( new SetAtterCmd(this, deltaAnger, deltaCharisma, deltaCourage) );
                continue;

            }

            // normal collision
            normalCollision( children[i], myQuery );

        }
    }

    // special alliance for peaceful
    if( PeacefulCollision > 2 ) {
        int deltaAnger = 0;
        int deltaCharisma = 0;
        int deltaCourage = +PeacefulCollision * 5;
        myQuery->addCmd( new SetAtterCmd(this, deltaAnger, deltaCharisma, deltaCourage) );
    }

}
