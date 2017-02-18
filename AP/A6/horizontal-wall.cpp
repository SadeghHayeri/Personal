#include "horizontal-wall.h"
#include "reflect-cmd.h"
#include "query.h"

bool HorizontalWall::contain( Child* child ) {

    coordinate p = child->getPosition();

    if( p.x >= startPoint.x && p.x <= startPoint.x + BLOCKSIZE && p.y >= startPoint.y && p.y <= endPoint.y + BLOCKSIZE )
        return true;
    return false;

}

bool HorizontalWall::collision( Child* child ) {

    coordinate p = child->getPosition();
    int radius = child->getRadius();


    // check for top and bottom line
    if( p.x >= startPoint.x && p.x <= endPoint.x + BLOCKSIZE ) {

        coordinate d;
        d.x = p.x;
        d.y = startPoint.y;

        if( getDistance( p, d ) <= radius );
            return true;

        d.y = startPoint.y + BLOCKSIZE;

        if( getDistance( p, d ) <= radius );
            return true;

    }

    // check for right and left line
    if( p.y >= startPoint.y && p.y <= startPoint.y + BLOCKSIZE ) {

        coordinate d;
        d.y = p.y;
        d.x = startPoint.x;

        if( getDistance( p, d ) <= radius );
            return true;

        d.x = endPoint.x + BLOCKSIZE;

        if( getDistance( p, d ) <= radius );
            return true;

    }

    // check for corners
    coordinate bl,tr,br;
    bl.x = startPoint.x;
    bl.y = startPoint.y + BLOCKSIZE;
    tr.x = endPoint.x + BLOCKSIZE;
    tr.y = endPoint.y;
    br.x = endPoint.x + BLOCKSIZE;
    br.y = endPoint.y + BLOCKSIZE;
    if( getDistance( p, startPoint ) <= radius || getDistance( p, tr ) <= radius || getDistance( p, bl ) <= radius || getDistance( p, br ) <= radius )
        return true;

    return false;

}

void HorizontalWall::reflect( Child* child, Query* myQuery ) {

    if( collision(child) ) {
        coordinate p = child->getPosition();

        // top or bottom of line
        if( p.x >= startPoint.x && p.x <= endPoint.x + BLOCKSIZE )
            myQuery->addCmd( new ReflectCmd(child, horizontal) );

        // right or left of line
        if( p.y >= startPoint.y && p.y <= startPoint.y + BLOCKSIZE )
            myQuery->addCmd( new ReflectCmd(child, vertical) );

        // check for corners
        coordinate d;
        if( p.x < startPoint.x && p.y < startPoint.y ) {
            d = startPoint;
        }
        else if( p.x < startPoint.x && p.y > startPoint.y + BLOCKSIZE ) {
            d = startPoint;
            d.y += BLOCKSIZE;
        }
        else if( p.x > endPoint.x + BLOCKSIZE && p.y > endPoint.y ) {
            d = endPoint;
            d.x += BLOCKSIZE;
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
