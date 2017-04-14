#ifndef _LOCAL_BOOK_H_
#define _LOCAL_BOOK_H_

using namespace std;
#include <string>
#include <vector>
#include <list>
#include "local_chapter.h"

class LocalBook {
public:
    LocalBook( string _name, vector< string > _authorsName ) : name(_name), authorsName(_authorsName) { synced = false; }

    void addChapter( string chapterName, int place );
    void addNewVersion( string chapterName, int id );
    void makeChange( string chapterName, int versionNum, ChangeLine* change );
    void downgrade( string chapterName, int versionNum );
    void editName( string newName ) { name = newName; }

    bool chapterExist( string chapterName );
    LocalChapter& findChapter( string chapterName );
    list<string> build( string chapterName, int versionNum );

    int getLastVersionNum( string chapterName );
    vector<int> getVersionList( string chapterName );
    string getName() { return name; }
    vector<string> getChapterList();
    vector<string> getAuthorsNames() { return authorsName; }
    vector<ChangeLine*> getChapterChanges( string chapterName, int versionNum );
    void setVersionId( string chapterName, int versionNum, int id );
    void setChapterSynced( string chapterName );
    bool isChapterSynced( string chapterName );
    void setSynced() { synced = true; }
    bool isSynced() { return synced; }


    void clear();
private:
    string name;
    vector<string> authorsName;
    bool synced;
    vector<LocalChapter> chapters;
};


#endif /* _LOCAL_BOOK_H_ */
