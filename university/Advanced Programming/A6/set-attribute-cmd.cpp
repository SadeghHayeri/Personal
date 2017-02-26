#include "set-attribute-cmd.h"
#include "child.h"

SetAtterCmd::SetAtterCmd( Child* _child, int _deltaRadius )
    : Command(_child), deltaRadius(_deltaRadius), deltaAnger(0), deltaCourage(0), deltaCharisma(0) {

    speedElements _deltaSpeed;
    _deltaSpeed.x = 0;
    _deltaSpeed.y = 0;
    deltaSpeed = _deltaSpeed;
}

SetAtterCmd::SetAtterCmd( Child* _child, int _deltaAnger, int _deltaCharisma, int _deltaCourage )
    : Command(_child), deltaRadius(0), deltaAnger(_deltaAnger), deltaCourage(_deltaCourage), deltaCharisma(_deltaCharisma) {

    speedElements _deltaSpeed;
    _deltaSpeed.x = 0;
    _deltaSpeed.y = 0;
    deltaSpeed = _deltaSpeed;
}


void SetAtterCmd::run() {

    speedElements speed =   child->getSpeed();
    int radius          =   child->getRadius();
    int anger           =   child->getAnger();
    int charisma        =   child->getCharisma();
    int courage         =   child->getCourage();

    speed.x     +=      deltaSpeed.x;
    speed.y     +=      deltaSpeed.y;
    radius      +=      deltaRadius;
    anger       +=      deltaAnger;
    charisma    +=      deltaCharisma;
    courage     +=      deltaCourage;

    child->setSpeed( speed );
    child->setRadius( radius );
    child->setAnger( anger );
    child->setCharisma( charisma );
    child->setCourage( courage );

}
