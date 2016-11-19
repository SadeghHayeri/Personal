#ifndef _SET_ATTRUBUTE_CMD_
#define _SET_ATTRUBUTE_CMD_

#include "command.h"
#include "utility.h"
class Child;

using namespace std;

class SetAtterCmd : public Command {
public:
    SetAtterCmd( Child* _child, int _deltaRadius );
    SetAtterCmd( Child* _child, int _deltaAnger, int _deltaCharisma, int _deltaCourage );
    SetAtterCmd( Child* _child, speedElements _deltaSpeed)
        : Command(_child), deltaRadius(0), deltaAnger(0), deltaCharisma(0), deltaCourage(0), deltaSpeed(_deltaSpeed) {};

    void run();
private:

    speedElements deltaSpeed;
    int deltaRadius;
    int deltaAnger;
    int deltaCharisma;
    int deltaCourage;

};

#endif /* _SET_ATTRUBUTE_CMD_ */
