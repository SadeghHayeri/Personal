#ifndef _CLIENT_H_
#define _CLIENT_H_

using namespace std;

#include "client_socket.h"
#include "interface.h"
#include "change_line.h"
#include "add_line.h"
#include "delete_line.h"
#include "edit_line.h"
#include "repository.h"
#include <iostream>
#include <list>

enum role { _SuperAdmin_, _Admin_, _User_ };

class Client {
public:
    Client( ClientSocket* _socket );
    string send( string command ); // edit for nexe time

    void run();

    void signUp( string userName, string password );
    bool login( string userName, string password );
    void logout();

    void addBook( string bookName, vector<string> authors );
    void addLocalBook( string bookName, vector<string> authors ) { repo.addBook(bookName, authors); }
    void addChapter( string bookName, string chapterName, int place = -1 );
    void addLocalChapter( string bookName, string chapterName, int place = -1 ) { repo.addChapter(bookName, chapterName, place); }
    void addNewVersion( string bookName, string chapterName );
    void addLocalNewVersion( string bookName, string chapterName, int id = 0 ) { repo.addNewVersion(bookName, chapterName, id); }
    void addLine( string bookName, string chapterName, int versionNum, int lineNum );
    void addLocalLine( string bookName, string chapterName, int versionNum, int lineNum ) { repo.makeChange(bookName, chapterName, versionNum, new AddLine(lineNum) ); }
    void deleteLine( string bookName, string chapterName, int versionNum, int lineNum );
    void deleteLocalLine( string bookName, string chapterName, int versionNum, int lineNum ) { repo.makeChange(bookName, chapterName, versionNum, new DeleteLine(lineNum) ); }
    void editLine( string bookName, string chapterName, int versionNum, int lineNum, string lineText );
    void editLocalLine( string bookName, string chapterName, int versionNum, int lineNum, string lineText ) { repo.makeChange(bookName, chapterName, versionNum, new EditLine(lineNum, lineText) ); }
    void setAccess( string userName, role accessLevel );
    role getRole();
    void syncBook( string bookName );
    void syncChapter( string bookName, string chapterName );
    void syncVersion( string bookName, string chapterName, int versionNum );
    void editBookName( string bookName, string newName );
    void editAuthors( string bookName, vector<string> authors );
    void editLocalBookName( string bookName, string newName ) { repo.editBookName(bookName, newName); }

    void addBookRequest();
    void downgrade( string bookName, string chapterName, int versionNum );
    void LocalDowngrade( string bookName, string chapterName, int versionNum ) { repo.downgrade(bookName, chapterName, versionNum); }
    void publishBook( string bookName );
    void download(string bookName, string fileAddress = "" );
    list<string> build( string bookName, string chapterName, int versionNum );

    void downloadVersion( string bookName, string chapterName, int versionNum, int id );
    void downloadLastVersion( string bookName, string chapterName );
    void giveAddBookAccess( string userName );
    int getLastVersionNum( string bookName, string chapterName );
    int getLocalLastVersionNum( string bookName, string chapterName ) { return repo.getLastVersionNum(bookName, chapterName); }
    vector<int> getVersionList( string bookName, string chapterName );
    vector<int> getLocalVersionList( string bookName, string chapterName ) { return repo.getVersionList(bookName, chapterName); }
    vector<string> getPublishedList();
    vector<string> getAuthorsNames( string bookName );
    vector<ChangeLine*> getChapterChanges( string bookName, string chapterName, int versionNum );
    vector<string> getRequests();
    vector<string> getChapterList( string bookName );
    vector<string> getLocalChapterList( string bookName ) { return repo.getChapterList(bookName); }
    vector<string> getBookList();
    vector<string> getLocalBookList() { return repo.getBookList(); }

private:
    ClientSocket* socket;
    Interface interface;
    Repository repo;
};

#endif /* _CLIENT_H_ */
