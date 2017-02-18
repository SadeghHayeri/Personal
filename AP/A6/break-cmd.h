#ifndef _BREAK_CMD_
#define _BREAK_CMD_

#include "command.h"

class Child;

using namespace std;

class BreakCmd : public Command {
public:
    BreakCmd( Child* _child ) : Command(_child) {};
    void setSimo( Simulation* _simo );
    void run();
private:
    Simulation* simo;
};

#endif /* _BREAK_CMD_ */
