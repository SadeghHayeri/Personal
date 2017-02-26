#include "local_version.h"
#include "change_line.h"

void LocalVersion::makeChange( ChangeLine* change ) {
    changes.push_back( change );
}

void LocalVersion::clear() {
    for (size_t i = 0; i < changes.size(); i++)
        delete changes[i];
    changes.clear();
}
