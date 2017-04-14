#ifndef _LOCAL_VERSION_H_
#define _LOCAL_VERSION_H_

#include <vector>
#include <string>
#include "change_line.h"

using namespace std;

class LocalVersion {
public:
    LocalVersion( int _id = 0 ) { id = _id; }
    void setId( int _id ) { id = _id; }

    void makeChange( ChangeLine* change );
    void clear();

    vector<ChangeLine*> getChanges() { return changes; }
    int getId() { return id; }
private:
    int id;
    vector< ChangeLine* > changes;
};

#endif /* _LOCAL_VERSION_H_ */
