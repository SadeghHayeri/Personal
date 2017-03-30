#ifndef _REPOSITORY_H_
#define _REPOSITORY_H_

#include <string>
#include <vector>
#include <list>
#include "local_book.h"

using namespace std;

class Repository {
public:

    void clear();

    // book
    void addBook( string bookName, vector<string> authorsName );
    bool bookExist( string bookName );
    LocalBook& findBook( string bookName );
    vector<string> getBookList();
    void editBookName( string bookName, string newName );
    void setBookSynced( string bookName );
    bool isBookSynced( string bookName );

    // chapter
    vector<ChangeLine*> getChapterChanges( string bookName, string chapterName, int versionNum );
    void addChapter( string bookName, string chapterName, int place = -1 );
    vector<string> getChapterList( string bookName );
    bool chapterExist( string bookName, string chapterName );//
    void setChapterSynced( string bookName, string chapterName );
    bool isChapterSynced( string bookName, string chapterName );

    // version
    void downgrade( string bookName, string chapterName, int versionNum );
    void addNewVersion( string bookName, string chapterName, int id );
    int getLastVersionNum( string bookName, string chapterName );
    vector<int> getVersionList( string bookName, string chapterName );
    bool versionExist( string bookName, string chapterName, int versionNum );//
    list<string> build( string bookName, string chapterName, int versionNum );
    vector<string> getAuthorsNames( string bookName );
    void setVersionId( string bookName, string chapterName, int versionNum, int id );

    // changeLine
    void makeChange( string bookName, string chapterName, int versionNum, ChangeLine* change );

private:
    vector< LocalBook > library;
};

#endif /* _REPOSITORY_H_ */
