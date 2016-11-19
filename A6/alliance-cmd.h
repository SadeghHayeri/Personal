#ifndef _ALLIANCE_CMD_H_
#define _ALLIANCE_CMD_H_

#include "command.h"
#include "utility.h"
class Child;

class AllianceCmd : public Command {
public:
    AllianceCmd( Child* _a, Child* _b );
    void run();
private:
    Child* b;
    speedElements aSpeed;
    speedElements bSpeed;
};

#endif /* _ALLIANCE_CMD_H_ */
