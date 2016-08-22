#include "book.h"
#include "exception.h"
#include <string>
#include <vector>
#include <algorithm>
#include "change_line.h"
#include <list>

Book::Book( string _name, User* _owner, vector< User* > _authors )
    : name(_name), owner(_owner), authors(_authors)
{
    authors.push_back( owner );
}

bool Book::chapterExist( string chapterName ) {
    for (size_t i = 0; i < chapters.size(); i++)
        if( chapters[i].getName() == chapterName )
            return true;
    return false;
}

void Book::downgrade( User& user, string chapterName, int versionNum ) {

    if( !(isOwner(user) || user.getRole() == _SuperAdmin_ || user.getRole() == _Admin_) )
        throw NotAccess( user.getName() );

    findChapter( chapterName ).downgrade( versionNum );

}

PublishedBook Book::publishBook( User& user ) {

    if( !(isOwner(user) || user.getRole() == _SuperAdmin_ || user.getRole() == _Admin_) )
        throw NotAccess( user.getName() );

    PublishedBook me;
    me.name = name;
    me.owner = owner->getName();

    for (size_t i = 0; i < authors.size(); i++)
        me.authors.push_back( authors[i]->getName() );

    for (size_t i = 0; i < chapters.size(); i++) {
        StringChapter tmp;
        tmp.name = chapters[i].getName();

        list<string> chapter = chapters[i].build( chapters[i].getLastVersionNum() );
        ::list<string>::iterator it = chapter.begin();
        for (size_t j = 0; j < chapter.size(); j++) {
            tmp.lines.push_back( *it );
            ++it;
        }

        me.chapters.push_back( tmp );
    }

    return me;

}

bool Book::isAuthor( User& user ) {
    for (size_t i = 0; i < authors.size(); i++)
        if( (*authors[i]).getName() == user.getName() )
            return true;
    return false;
}

bool Book::isOwner( User& user ) {
    if( (*owner).getName() == user.getName() )
        return true;
    return false;
}

void Book::addChapter( User& user, string chapterName, int place ) {

    // check for chapter exist
    if( chapterExist(chapterName) )
        throw ChapterExist( chapterName );

    // check accesses
    if( !isAuthor( user ) )
        throw NotAccess( user.getName() );

    // if palce overflow ,fix it
    place = (place > (int)chapters.size()) ? chapters.size()-1 : place;

    if( place < 0 ) {
        chapters.push_back( Chapter(chapterName) );
        chapters[ chapters.size()-1  ].addNewVersion();
    }

    else {
        chapters.insert( chapters.begin() + place, Chapter(chapterName) );
        chapters[ place ].addNewVersion();
    }

}

vector<string> Book::getChapterList( User& user) {

    if( !(isAuthor(user) || user.getRole() == _SuperAdmin_ || user.getRole() == _Admin_) )
        throw NotAccess( user.getName() );

    vector<string> list;
    for (size_t i = 0; i < chapters.size(); i++)
        list.push_back( chapters[i].getName() );
    return list;
}

Chapter& Book::findChapter( string chapterName ) {

    for (size_t i = 0; i < chapters.size(); i++)
        if( chapters[i].getName() == chapterName )
            return chapters[i];

    throw ChapterNotExist( chapterName );

}

void Book::addNewVersion( User& user, string chapterName ) {

    // check accesses
    if( !isAuthor( user ) )
        throw NotAccess( user.getName() );

    findChapter( chapterName ).addNewVersion();

}

int Book::getLastVersionNum( User& user, string chapterName ) {

    // check accesses
    if( !isAuthor( user ) )
        throw NotAccess( user.getName() );

    return findChapter( chapterName ).getLastVersionNum();

}

vector<int> Book::getVersionList( User& user, string chapterName ) {

    // check accesses
    if( !(isAuthor(user) || user.getRole() == _SuperAdmin_ || user.getRole() == _Admin_) )
        throw NotAccess( user.getName() );

    return findChapter( chapterName ).getVersionList();

}

void Book::makeChange( User& user, string chapterName, int versionNum, ChangeLine* change ) {

    // check accesses
    if( !isAuthor( user ) )
        throw NotAccess( user.getName() );

    findChapter( chapterName ).makeChange( versionNum, change );
}

vector<ChangeLine*> Book::getChapterChanges( User& user, string chapterName, int versionNum ) {

    if( !(isAuthor(user) || user.getRole() == _SuperAdmin_ || user.getRole() == _Admin_) )
        throw NotAccess( user.getName() );

    return findChapter( chapterName ).getChapterChanges( versionNum );
}

vector<User*> Book::getAuthors( User& user ) {
    if( !(isAuthor(user) || user.getRole() == _SuperAdmin_ || user.getRole() == _Admin_) )
        throw NotAccess( user.getName() );

    return authors;
}

void Book::editName( User& user, string newName ) {
    if( !(isOwner(user) || user.getRole() == _SuperAdmin_ || user.getRole() == _Admin_) )
        throw NotAccess( user.getName() );

    name = newName;
}

void Book::editAuthors( vector< User* > _authors ) {
    authors = _authors;
}

void Book::clear() {
    for (size_t i = 0; i < chapters.size(); i++)
        chapters[i].clear();
    chapters.clear();
    authors.clear();
}
