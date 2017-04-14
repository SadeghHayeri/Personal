#include "vertical-wall.h"
#include "reflect-cmd.h"
#include "query.h"

bool VerticalWall::contain( Child* child ) {

    coordinate p = child->getPosition();

    if( p.x >= startPoint.x && p.x <= startPoint.x + BLOCKSIZE && p.y >= startPoint.y && p.y <= endPoint.y + BLOCKSIZE )
        return true;
    return false;

}

bool VerticalWall::collision( Child* child ) {

    coordinate p = child->getPosition();
    int radius = child->getRadius();


    // check for right and left line
    if( p.y >= startPoint.y && p.y <= endPoint.y + BLOCKSIZE ) {

        coordinate d;
        d.x = startPoint.x;
        d.y = p.y;

        if( getDistance( p, d ) <= radius );
            return true;

        d.x = startPoint.x + BLOCKSIZE;

        if( getDistance( p, d ) <= radius );
            return true;

    }

    // check for top and bottom line
    if( p.x >= startPoint.x && p.x <= startPoint.x + BLOCKSIZE ) {

        coordinate d;
        d.x = p.x;
        d.y = startPoint.y;

        if( getDistance( p, d ) <= radius );
            return true;

        d.y = endPoint.y + BLOCKSIZE;

        if( getDistance( p, d ) <= radius );
            return true;

    }

    // check for corners
    coordinate tr, bl, br;
    tr.x = startPoint.x + BLOCKSIZE;
    tr.y = startPoint.y;
    bl.x = endPoint.x;
    bl.y = endPoint.y + BLOCKSIZE;
    br.x = endPoint.x + BLOCKSIZE;
    br.y = endPoint.y + BLOCKSIZE;
    if( getDistance( p, startPoint ) <= radius || getDistance( p, tr ) <= radius || getDistance( p, bl ) <= radius || getDistance( p, br ) <= radius )
        return true;

    return false;

}

void VerticalWall::reflect( Child* child, Query* myQuery ) {

    if( collision(child) ) {
        coordinate p = child->getPosition();

        // right or left of line
        if( p.y >= startPoint.y && p.y <= endPoint.y + BLOCKSIZE )
            myQuery->addCmd( new ReflectCmd(child, vertical) );

        // top or bottom of line
        if( p.x >= startPoint.x && p.x <= startPoint.x + BLOCKSIZE )
            myQuery->addCmd( new ReflectCmd(child, horizontal) );

        // check for corners
        coordinate d;
        if( p.x < startPoint.x && p.y < startPoint.y ) {
            d = startPoint;
        }
        else if( p.x > startPoint.x + BLOCKSIZE && p.y < startPoint.y ) {
            d = startPoint;
            d.x += BLOCKSIZE;
        }
        else if( p.x < endPoint.x && p.y > endPoint.y + BLOCKSIZE ) {
            d = endPoint;
            d.y += BLOCKSIZE;
        }
        else {
            d = endPoint;
            d.x += BLOCKSIZE;
            d.y += BLOCKSIZE;
        }

        d = p - d;

        if( abs(d.x) > abs(d.y) )
            myQuery->addCmd( new ReflectCmd(child, vertical) );
        else if( abs(d.x) < abs(d.y) )
            myQuery->addCmd( new ReflectCmd(child, horizontal) );
        else {
            myQuery->addCmd( new ReflectCmd(child, vertical) );
            myQuery->addCmd( new ReflectCmd(child, horizontal) );
        }

    }

}
