#ifndef _SERVER_H_
#define _SERVER_H_

#include "database.h"
#include "user.h"
#include "user_list.h"
#include "server.h"
#include "logger.h"
using namespace std;

const string logfileAddress = "server.log";

class MyServer : public Server {
public:
    MyServer(int port) : Server(port), log( logfileAddress ) { loadCmds(); log.line(); }
    void on_standard_input(string line);
    void on_new_connection(int identifier);
    void on_new_message(int identifier, string message);
    void on_terminated_connection(int identifier);

    string cmd( int identifier, string command );

    bool login( int identifier, string userName, string password );
    void logout( int identifier );
    void addBookRequest( int identifier );
    string addUser( string userName, string password );
    string addBook( int identifier, string bookName, vector<string> authors );
    string addChapter( int identifier, string bookName, string chapterName, int place );
    string addNewVersion( int identifier, string bookName, string chapterName );
    string addLine( int identifier, string bookName, string chapterName, int versionNum, int lineNum );
    string deleteLine( int identifier, string bookName, string chapterName, int versionNum, int lineNum );
    string editLine( int identifier, string bookName, string chapterName, int versionNum, int lineNum, string lineText );
    string setAccess( int identifier, string userName, role accessLevel );
    string getRole( int identifier );
    string giveAddBookAccess( int identifier, string userName );
    string downgrade( int identifier, string bookName, string chapterName, int versionNum );
    string getAuthorsNames( int identifier, string bookName );
    string publishBook( int identifier, string bookName );
    string download( string bookName );
    string editBookName( int identifier, string bookName, string newName );
    string editAuthors( int identifier, string bookName, vector<string> authors );

    string getRequests( int identifier );
    string getLastVersionNum( int identifier, string bookName, string chapterName );
    string getVersionList( int identifier, string bookName, string chapterName );
    string getChapterChanges( int identifier, string bookName, string chapterName, int versionNum );
    string getBookList();
    string getPublishedList();
    string getChapterList( int identifier, string bookName );

    void saveCmd( int identifier, string command );
    void loadCmds();
private:
    Database db;
    UserList onlineUsers;
    Logger log;
};

#endif /* _SERVER_H_ */
