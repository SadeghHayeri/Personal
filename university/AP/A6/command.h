#ifndef _COMMAND_H_
#define _COMMAND_H_

class Child;
class Simulation;

class Command {
public:
    Command( Child* _child ) : child(_child) {};
    virtual void run() = 0;
protected:
    Child* child;
};

#endif /* _COMMAND_H_ */
