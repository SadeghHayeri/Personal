#ifndef _VERSION_H_
#define _VERSION_H_

#include <vector>
#include "change_line.h"

using namespace std;

class Version {
public:
    Version( int _versionNum, int _id ) { id = _id; }
    void makeChange( ChangeLine* change );
    void clear();

    int getId() { return id; }
    vector<ChangeLine*> getChanges() { return changes; }
private:
    int id;
    vector< ChangeLine* > changes;
};

#endif /* _VERSION_H_ */
