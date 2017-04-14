#ifndef _BOOK_H_
#define _BOOK_H_

#include <string>
#include <vector>
#include "chapter.h"
#include "user.h"

using namespace std;

struct StringChapter {
    string name;
    vector<string> lines;
};

struct PublishedBook {
    string name;
    string owner;
    vector<string> authors;
    vector <StringChapter> chapters;
};


class Book {
public:
    Book( string _name, User* _owner, vector< User* > _authors );

    void addChapter( User& user, string chapterName, int place );
    void addNewVersion( User& user, string chapterName );
    void makeChange( User& user, string chapterName, int versionNum, ChangeLine* change );
    void downgrade( User& user, string chapterName, int versionNum );
    void editName( User& user, string newName );
    void editAuthors( vector< User* > _authors );
    void clear();

    Chapter& findChapter( string chapterName );
    PublishedBook publishBook( User& user );
    bool chapterExist( string chapterName );
    bool isAuthor( User& user );
    bool isOwner( User& user );

    int getLastVersionNum( User& user, string chapterName );
    vector<int> getVersionList( User& user, string chapterName );
    string getName() { return name; }
    vector<string> getChapterList( User& user );
    vector<User*> getAuthors( User& user);
    vector<ChangeLine*> getChapterChanges( User& user, string chapterName, int versionNum );
private:
    string name;
    User* owner;
    vector< User* > authors;
    vector< Chapter > chapters;
};

#endif /* _BOOK_H_ */
