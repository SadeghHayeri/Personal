#include <cmath>
#include "break-cmd.h"
#include "utility.h"
#include "child.h"
#include "simulation.h"

void BreakCmd::setSimo( Simulation* _simo ) {
    simo = _simo;
}

void BreakCmd::run() {

    if( child->checkLife() ) {
        speedElements speed = child->getSpeed();

        float posX = child->getPosition().x;
        float posY = child->getPosition().y;

        int radius = child->getRadius();
        int id = simo->getMaxId();

        int anger = child->getAnger();
        int charisma = child->getCharisma();
        int courage = child->getCourage();

        bool fragile = true;

        for (size_t i = 0; i < 6; i++) {

            speedElements childSpeed;
            childSpeed.x = speed.x / 6 * cos( i * 60 * PI / 180 );
            childSpeed.y = speed.y / 6 * sin( i * 60 * PI / 180 );

            float childPosX = posX + radius * (2.0/3) * cos(i * PI / 3);

            float childPosY = posY + radius * (2.0/3) * sin(i * PI / 3);

            int childRadius = radius / 3;
            int childId = id + i + 1;

            Child* newChild;
            if( child->getType() == "Angry" )
                newChild = new AngryChild( childId, childRadius, childPosX, childPosY, childSpeed.x, childSpeed.y, anger, charisma, courage, fragile );
            else if( child->getType() == "Peaceful" )
                newChild = new PeacefulChild( childId, childRadius, childPosX, childPosY, childSpeed.x, childSpeed.y, anger, charisma, courage, fragile );
            else if( child->getType() == "Coward" )
                newChild = new CowardChild( childId, childRadius, childPosX, childPosY, childSpeed.x, childSpeed.y, anger, charisma, courage, fragile );
            simo->addChild( newChild );

        }

        simo->remove( child );
    }

}
