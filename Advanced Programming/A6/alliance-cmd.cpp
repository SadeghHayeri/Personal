#include "alliance-cmd.h"
#include "child.h"
AllianceCmd::AllianceCmd( Child* _a, Child* _b )
    : Command(_a) {
    b = _b;
    aSpeed = _a->getSpeed();
    bSpeed = _b->getSpeed();
}

void AllianceCmd::run() {
    speedElements midSpeed;
    midSpeed.x = (aSpeed.x + bSpeed.x) / 2;
    midSpeed.y = (aSpeed.y + bSpeed.y) / 2;
    child->setSpeed( midSpeed );
    b->setSpeed( midSpeed );
}
