#ifndef _CHAPTER_H_
#define _CHAPTER_H_

#include <vector>
#include <string>
#include "version.h"
#include <list>

using namespace std;

class Chapter {
public:
    Chapter( string _name ) : name(_name), versionCounter(0) {};

    void addNewVersion();
    void makeChange( int versionNum, ChangeLine* change );
    void downgrade( int versionNum );
    void clear();

    Version& findVersion( size_t versionNum );
    list<string> build( int versionNum );

    Version& getLastVersion();
    vector<ChangeLine*> getChapterChanges( int versionNum );
    int getLastVersionNum();
    vector<int> getVersionList();
    string getName() { return name; }
private:
    string name;
    vector< Version > versions;
    int versionCounter;
};

#endif /* _CHAPTER_H_ */
