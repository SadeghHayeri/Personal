#include "reflect-cmd.h"
#include "utility.h"
#include "child.h"
void ReflectCmd::run() {

    speedElements speed = child->getSpeed();

    if( type == horizontal )
        speed.y *= -1;
    else
        speed.x *= -1;

    child->setSpeed( speed );
    
}
