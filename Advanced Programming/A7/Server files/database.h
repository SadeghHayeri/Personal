#ifndef _DATA_BASE_H_
#define _DATA_BASE_H_

#include <string>
#include <vector>
#include "book.h"
#include "user.h"

const string adminUsername = "admin";
const string adminPassword = "password";

using namespace std;

class Database {
public:

    Database();

    /////// User manager
    void addUser( string userName, string password );
    void addBookRequest( User& user );
    void setAccess( User& user, string userName, role accessLevel );
    role getRole( User& user );
    void defineSuperAdmin( string userName, string password );
    void giveAddBookAccess( User& user, string userName );

    User& findUser( string usersName );

    bool adminAccess( User& user );
    bool superAdminAccess( User& user );
    bool userExist( string userName );
    bool authentication( string userName, string password );
    User* getUser( string userName );
    vector< User* > getUsers( vector<string> usersName );
    vector<User*> getRequests( User& user );


    /////// Book manager
    void addBook( string bookName, User& owner, vector<string> authorsName );
    void editBookName( User& user, string bookName, string newName );
    void editAuthors( User& owner, string bookName, vector<string> authorsName );

    bool bookExist( string bookName );
    void publishBook( User& user, string bookName );
    PublishedBook download( string bookName );

    vector<string> getBookList();
    vector<string> getPublishedList();
    Book& findBook( string bookName );
    vector<ChangeLine*> getChapterChanges( User& user, string bookName, string chapterName, int versionNum );
    vector<User*> getAuthors( User& user, string bookName );


    /////// chapter
    void addChapter( User& user, string bookName, string chapterName, int place = -1 );
    void downgrade( User& user, string bookName, string chapterName, int versionNum );

    vector<string> getChapterList( User& user, string bookName );

    /////// Version
    void addNewVersion( User& user, string bookName, string chapterName );

    int getLastVersionNum( User& user, string bookName, string chapterName );
    vector<int> getVersionList( User& user, string bookName, string chapterName );

    /////// ChangeLine
    void makeChange( User& user, string bookName, string chapterName, int versionNum, ChangeLine* change );
private:
    vector< Book* > library;
    vector< User > users;
    vector< User* > requsetList;
    vector< PublishedBook > publishedBooks;
};

#endif /* _DATA_BASE_H_ */
