#ifndef _LOCAL_CHAPTER_H_
#define _LOCAL_CHAPTER_H_

using namespace std;
#include <string>
#include <vector>
#include <list>
#include "local_version.h"

class LocalChapter {
public:
    LocalChapter( string _name ) : name(_name) { synced = false; }

    void addNewVersion( int id = 0 );
    void setVersionId( int id );
    void makeChange( int versionNum, ChangeLine* change );

    void downgrade( int versionNum );
    void clear();
    list<string> build( int versionNum );

    int getLastVersionNum();
    vector<int> getVersionList();
    LocalVersion& getLastVersion();
    string getName() { return name; }
    LocalVersion& findVersion( size_t versionNum );
    vector<ChangeLine*> getChapterChanges( int versionNum );
    void setVersionId( int versionNum, int id );
    void setSynced() { synced = true; }
    bool isSynced() { return synced; }

private:
    bool synced;
    string name;
    vector<LocalVersion> versions;
    vector< list<string> >lastBuilds;
};


#endif /* _LOCAL_CHAPTER_H_ */
