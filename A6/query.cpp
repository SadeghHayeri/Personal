#include "query.h"
#include "break-cmd.h"
#include "set-attribute-cmd.h"
#include "alliance-cmd.h"
#include "reflect-cmd.h"
#include "command.h"
#include <iostream>

void Query::setSimo( Simulation* _simo ) {
    simo = _simo;
}

void Query::clear() {
    for (size_t i = 0; i < commands.size(); i++)
        delete commands[i];
    commands.clear();
}

void Query::addCmd( Command* cmd ) {

    // if cmd is break-cmd, we need set simulation address for it to recall!
    BreakCmd* bCmd = dynamic_cast<BreakCmd*>(cmd);
    if( bCmd ) {
        bCmd->setSimo( simo );
    }

    commands.push_back( cmd );
}

void Query::runCommands() {

    // 1. set-attribute-cmd
    for (size_t i = 0; i < commands.size(); i++)
        if( dynamic_cast<SetAtterCmd*>(commands[i]) )
            commands[i]->run();

    // 2. reflect-cmd
    for (size_t i = 0; i < commands.size(); i++)
        if( dynamic_cast<ReflectCmd*>(commands[i]) )
            commands[i]->run();

    // 3. alliance-cmd
    for (size_t i = 0; i < commands.size(); i++)
        if( dynamic_cast<AllianceCmd*>(commands[i]) )
            commands[i]->run();

    // 4. break-cmd
    for (size_t i = 0; i < commands.size(); i++)
        if( dynamic_cast<BreakCmd*>(commands[i]) )
            commands[i]->run();

    clear();

}
