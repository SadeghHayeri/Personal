#include "repository.h"
#include "exception.h"

// book
void Repository::addBook( string bookName, vector<string> authorsName ) {
    if( bookExist(bookName) )
        throw BookExist( bookName );
    library.push_back( LocalBook(bookName, authorsName) );
}

bool Repository::bookExist( string bookName ) {
    for (size_t i = 0; i < library.size(); i++)
        if( library[i].getName() == bookName )
            return true;
    return false;
}

LocalBook& Repository::findBook( string bookName ) {
    for (size_t i = 0; i < library.size(); i++)
        if( library[i].getName() == bookName )
            return library[i];
    throw BookNotExist( bookName );
}

vector<string> Repository::getBookList() {
    vector<string> bookList;
    for (size_t i = 0; i < library.size(); i++)
        bookList.push_back( library[i].getName() );
    return bookList;
}

void Repository::editBookName( string bookName, string newName ) {
    findBook(bookName).editName( newName );
}

// chapter
vector<ChangeLine*> Repository::getChapterChanges( string bookName, string chapterName, int versionNum ) {
    return findBook( bookName ).getChapterChanges( chapterName, versionNum );
}

void Repository::addChapter( string bookName, string chapterName, int place ) {
    findBook( bookName ).addChapter( chapterName, place );
}
vector<string> Repository::getChapterList( string bookName ) {
    return findBook( bookName ).getChapterList();
}

// version
void Repository::downgrade( string bookName, string chapterName, int versionNum ) {
    findBook( bookName ).downgrade( chapterName, versionNum );
}

void Repository::addNewVersion( string bookName, string chapterName, int id ) {
    findBook( bookName ).addNewVersion( chapterName, id );
}

int Repository::getLastVersionNum( string bookName, string chapterName ) {
    return findBook( bookName ).getLastVersionNum( chapterName );
}

vector<int> Repository::getVersionList( string bookName, string chapterName ) {
    return findBook( bookName ).getVersionList( chapterName );
}

// changeLine
void Repository::makeChange( string bookName, string chapterName, int versionNum, ChangeLine* change ) {
    findBook( bookName ).makeChange( chapterName, versionNum, change );
}

bool Repository::chapterExist( string bookName, string chapterName ) {
    if( bookExist(bookName) ) {
        return findBook(bookName).chapterExist(chapterName);
    }
    return false;
}

bool Repository::versionExist( string bookName, string chapterName, int versionNum ) {
    if( chapterExist( bookName, chapterName) ) {
        return (findBook(bookName).findChapter(chapterName).getLastVersionNum() == versionNum);
    }
    return false;
}

list<string> Repository::build( string bookName, string chapterName, int versionNum ) {
    return findBook( bookName ).build( chapterName, versionNum );
}

void Repository::clear() {
    for (size_t i = 0; i < library.size(); i++)
        library[i].clear();
    library.clear();
}

void Repository::setVersionId( string bookName, string chapterName, int versionNum, int id ) {
    findBook( bookName ).setVersionId( chapterName, versionNum, id );
}

vector<string> Repository::getAuthorsNames( string bookName ) {
    return findBook( bookName ).getAuthorsNames();
}

void Repository::setBookSynced( string bookName ) {
    findBook( bookName ).setSynced();
}

bool Repository::isBookSynced( string bookName ) {
    return findBook( bookName ).isSynced();
}

void Repository::setChapterSynced( string bookName, string chapterName ) {
    findBook( bookName ).setChapterSynced( chapterName );
}

bool Repository::isChapterSynced( string bookName, string chapterName ) {
    return findBook( bookName ).isChapterSynced( chapterName );
}
