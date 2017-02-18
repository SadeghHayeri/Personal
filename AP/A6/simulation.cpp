#include "simulation.h"
#include <iomanip>
#include <iostream>

Simulation::Simulation( Map* _map, int _dt, int _T )
    : map(_map), dt(_dt), T(_T), upTime(0) {
    myQuery.setSimo( this );
    maxId = -1;
}

void Simulation::addChild( Child* newChild ) {
    if( newChild->getId() > maxId )
        maxId = newChild->getId();
    children.push_back( newChild );
}

void Simulation::getChildsFromInput() {

        string line;
        while( getline( cin, line ) ) {
            line = replaceAll( line, ',', ' ');
            std::stringstream mySream(line);

            int id;
            string type;
            string fragileStr;
            float posX, posY;
            float vX, vY;
            int radius;
            int anger;
            int charisma;
            int courage;

            mySream >> id;
            mySream >> type;
            mySream >> fragileStr;
            mySream >> posX;
            mySream >> posY;
            mySream >> vX;
            mySream >> vY;
            mySream >> radius;
            mySream >> anger;
            mySream >> charisma;
            mySream >> courage;

            bool fragile = (fragileStr=="true");

            Child* newChild;
            if( type == "Angry" )
                newChild = new AngryChild( id, radius, posX, posY, vX, vY, anger, charisma, courage, fragile );
            else if( type == "Peaceful" )
                newChild = new PeacefulChild( id, radius, posX, posY, vX, vY, anger, charisma, courage, fragile );
            else if( type == "Coward" )
                newChild = new CowardChild( id, radius, posX, posY, vX, vY, anger, charisma, courage, fragile );
            else
                throw std::invalid_argument( "invalid child type!" );

            addChild( newChild );
        }

}

bool compareById( Child* a, Child* b) {
    return a->getId() < b->getId();
}

void Simulation::checkHits() {
    for (size_t i = 0; i < children.size(); i++) {
        map->reflect( children[i], &myQuery );
        children[i]->checkAllCollision( children, &myQuery );
    }
}

void Simulation::moveAll( int dt ) {
    for (size_t i = 0; i < children.size(); i++)
        children[i]->move(dt);
}

void Simulation::removeDeadChilds() {
    for (size_t i = 0; i < children.size(); i++)
        if( !children[i]->checkLife() ) {
            remove( children[i] );
            i--;
        }
}

void Simulation::start() {

    // first result
    printResult();
    upTime+=dt;

    while( upTime != T + dt ) {

        // sort
        std::sort( children.begin(), children.end(), compareById );


        // moveAll
        moveAll( dt );

        // checkAll
        checkHits();

        // progress query
        myQuery.runCommands();

        // print result
        printResult();

        // remove all dead child
        removeDeadChilds();

        upTime += dt;
    }
}

void Simulation::printResult() {
    cout << "#" << upTime/dt << endl;
    for (size_t i = 0; i < children.size(); i++) {

        if( !children[i]->checkLife() ) {
            cout << children[i]->getId() << ", KIA" << endl;
        } else {
            float posX = children[i]->getPosition().x;
            float posY = children[i]->getPosition().y;
            cout << std::fixed << std::setprecision(1);
            cout << children[i]->getId() << ", " << children[i]->getType() << ", " << posX << ", " << posY << ", " << children[i]->getRadius() <<  ", " << children[i]->getAnger() << ", " <<  children[i]->getCharisma() << ", " <<  children[i]->getCourage() << endl;
        }

    }
}

void Simulation::remove( Child* child ) {
    for (size_t i = 0; i < children.size(); i++) {
        if( children[i] == child ) {
            children.erase(children.begin()+i);
            delete child;
            return;
        }
    }
    throw std::invalid_argument( "can't find child with this address!" );
}
