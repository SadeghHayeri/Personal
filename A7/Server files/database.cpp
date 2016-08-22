#include "database.h"
#include "exception.h"
#include <algorithm>
#include "change_line.h"

Database::Database() {
    defineSuperAdmin( adminUsername, adminPassword );
}

void Database::defineSuperAdmin( string userName, string password ) {
    addUser( userName, password );
    findUser( userName ).setAccess( _SuperAdmin_ );
    findUser( userName ).giveAddBookAccess();
}

/////// user manager
void Database::addUser( string userName, string password ) {

    // check user exist
    if( userExist(userName) )
        throw UserExist( userName );

    users.push_back( User(userName, password) );

}

void Database::downgrade( User& user, string bookName, string chapterName, int versionNum ) {

    findBook( bookName ).downgrade( user, chapterName, versionNum );

}

bool Database::adminAccess( User& user ) {
    if( user.getRole() == _SuperAdmin_ || user.getRole() == _Admin_ )
        return true;
    return false;
}

bool Database::superAdminAccess( User& user ) {
    if( user.getRole() == _SuperAdmin_ )
        return true;
    return false;
}

User& Database::findUser( string userName ) {

    for (size_t i = 0; i < users.size(); i++) {
        if( users[i].getName() == userName )
            return users[i];
    }

    throw UserNotExist( userName );

}

vector< User* > Database::getUsers( vector<string> usersName ) {

    vector< User* > usersPointer;
    for (size_t i = 0; i < usersName.size(); i++)
        usersPointer.push_back( &findUser(usersName[i]) );
    return usersPointer;

}

bool Database::userExist( string usersName ) {
    for (size_t i = 0; i < users.size(); i++)
        if( users[i].getName() == usersName )
            return true;
    return false;
}

bool Database::authentication( string userName, string password ) {

    try{
        return findUser( userName ).authentication( password );
    }
    catch( UserNotExist ) {
        return false;
    }

}

vector<User*> Database::getRequests( User& user ) {
    if( !adminAccess( user ) )
        throw NotAccess( user.getName() );
    return requsetList;
}

void Database::setAccess( User& user, string userName, role accessLevel ) {

    if( !superAdminAccess( user ) )
        throw NotAccess( user.getName() );

    findUser( userName ).setAccess( accessLevel );

}

role Database::getRole( User& user ) {
    return user.getRole();
}

/////// book manager
void Database::addBookRequest( User& user ) {
    requsetList.push_back( &user );
}

vector<User*> Database::getAuthors( User& user, string bookName ) {
    return findBook(bookName).getAuthors( user );
}

void Database::addBook( string userName, User& owner, vector<string> authorsName ) {

    // check owner can add a newbook
    if( !owner.canAddBook() )
        throw NotAccess( owner.getName() );

    // check book exist
    if( bookExist(userName) )
        throw BookExist( userName );

    // check authorsName exist
    for (size_t i = 0; i < authorsName.size(); i++)
        if( !userExist(authorsName[i]) )
            throw UserNotExist( userName );

    // remove owner from authorsName list
    for (size_t i = 0; i < authorsName.size(); i++)
        if( authorsName[i] == owner.getName() ) {
            authorsName.erase( authorsName.begin() + i );
            i--;
        }

    library.push_back( new Book( userName, &owner, getUsers(authorsName) ) );
///////////////...................
}

void Database::editAuthors( User& owner, string bookName, vector<string> authorsName ) {

    // check authorsName exist
    for (size_t i = 0; i < authorsName.size(); i++)
        if( !userExist(authorsName[i]) )
            throw UserNotExist( authorsName[i] );

    // remove owner from authorsName list
    for (size_t i = 0; i < authorsName.size(); i++)
        if( authorsName[i] == owner.getName() ) {
            authorsName.erase( authorsName.begin() + i );
            i--;
        }

    findBook( bookName ).editAuthors( getUsers(authorsName) );

}

bool Database::bookExist( string bookName ) {
    for (size_t i = 0; i < library.size(); i++)
        if( library[i]->getName() == bookName )
            return true;
    return false;
}

Book& Database::findBook( string bookName ) {

    for (size_t i = 0; i < library.size(); i++)
        if( library[i]->getName() == bookName )
            return *library[i];

    throw BookNotExist( bookName );

}

void Database::publishBook( User& user, string bookName ) {

    // get book
    PublishedBook newly = findBook( bookName ).publishBook( user );

    // delete from library
    findBook( bookName ).clear();
    for (size_t i = 0; i < library.size(); i++)
        if( library[i]->getName() == bookName ) {
            library.erase( library.begin() + i );
            break;
        }

    // insert in publishedLibrary
    publishedBooks.push_back(newly);

}

vector<string> Database::getBookList() {
    vector<string> list;
    for (size_t i = 0; i < library.size(); i++)
        list.push_back( library[i]->getName() );
    return list;
}

void Database::giveAddBookAccess( User& user, string userName ) {

    // check accessLevel
    if( !adminAccess( user ) )
        throw NotAccess( user.getName() );

    // erase name from requsetList
    for (size_t i = 0; i < requsetList.size(); i++) {
        if( requsetList[i]->getName() == userName ) {
            requsetList.erase( requsetList.begin() + i );
            i--;
        }
    }

    // get AddBook access
    findUser( userName ).giveAddBookAccess();

}

void Database::addChapter( User& user, string bookName, string chapterName, int place ) {
    findBook( bookName ).addChapter( user, chapterName, place );
}

vector<string> Database::getChapterList( User& user, string bookName ) {
    return findBook( bookName ).getChapterList( user );
}

void Database::addNewVersion( User& user, string bookName, string chapterName ) {
    findBook( bookName ).addNewVersion( user, chapterName );
}

int Database::getLastVersionNum( User& user, string bookName, string chapterName ) {
    return findBook( bookName ).getLastVersionNum( user, chapterName );
}

vector<int> Database::getVersionList( User& user, string bookName, string chapterName ) {
    return findBook( bookName ).getVersionList( user, chapterName );
}

void Database::makeChange( User& user, string bookName, string chapterName, int versionNum, ChangeLine* change ) {
    findBook( bookName ).makeChange( user, chapterName, versionNum, change );
}

vector<ChangeLine*> Database::getChapterChanges( User& user, string bookName, string chapterName, int versionNum ) {
    return findBook( bookName ).getChapterChanges( user, chapterName, versionNum );
}

vector<string> Database::getPublishedList() {
    vector<string> list;
    for (size_t i = 0; i < publishedBooks.size(); i++)
        list.push_back( publishedBooks[i].name );
    return list;
}

PublishedBook Database::download( string bookName ) {
    for (size_t i = 0; i < publishedBooks.size(); i++)
        if( publishedBooks[i].name == bookName )
            return publishedBooks[i];
    throw BookNotExist( bookName );
}

void Database::editBookName( User& user, string bookName, string newName ) {

    if( bookName != newName ) {
        if( bookExist(newName) )
            throw BookExist( newName );
        findBook( bookName ).editName( user, newName );
    }
}
