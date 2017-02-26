#ifndef _REFLECT_CMD_
#define _REFLECT_CMD_

#include "command.h"

class Child;

using namespace std;

enum reflectType { horizontal, vertical };

class ReflectCmd : public Command {
public:
    ReflectCmd( Child* _child, reflectType _type ) : Command(_child), type(_type) {};
    void run();
private:
    reflectType type;
};

#endif /* _REFLECT_CMD_ */
