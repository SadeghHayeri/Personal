#ifndef _QUERY_H_
#define _QUERY_H_

#include <vector>
#include "command.h"
class Command;
class Simulation;

using namespace std;

class Query {
public:
    void setSimo( Simulation* _simo );
    void addCmd( Command* cmd );
    void runCommands();
    void clear();
private:
    vector< Command* > commands;
    Simulation* simo;
};

#endif /* _QUERY_H_ */
