#include "local_book.h"
#include "local_chapter.h"
#include "exception.h"

bool LocalBook::chapterExist( string chapterName ) {
    for (size_t i = 0; i < chapters.size(); i++)
        if( chapters[i].getName() == chapterName )
            return true;
    return false;
}

void LocalBook::addChapter( string chapterName, int place ) {

    // check for chapter exist
    if( chapterExist(chapterName) )
        throw ChapterExist( chapterName );

    // if palce overflow ,fix it
    place = (place > (int)chapters.size()) ? chapters.size()-1 : place;

    if( place < 0 ) {
        chapters.push_back( LocalChapter(chapterName) );
        chapters[ chapters.size()-1  ].addNewVersion();
    }

    else {
        chapters.insert( chapters.begin() + place, LocalChapter(chapterName) );
        chapters[ place ].addNewVersion();
    }

}

vector<string> LocalBook::getChapterList() {
    vector<string> chapterList;
    for (size_t i = 0; i < chapters.size(); i++)
        chapterList.push_back( chapters[i].getName() );
    return chapterList;
}

LocalChapter& LocalBook::findChapter( string chapterName ) {
    for (size_t i = 0; i < chapters.size(); i++)
        if( chapters[i].getName() == chapterName )
            return chapters[i];
    throw ChapterNotExist( chapterName );
}

void LocalBook::addNewVersion( string chapterName, int id ) {
    findChapter( chapterName ).addNewVersion( id );
}

int LocalBook::getLastVersionNum( string chapterName ) {
    return findChapter( chapterName ).getLastVersionNum();
}

vector<int> LocalBook::getVersionList( string chapterName ) {
    return findChapter( chapterName ).getVersionList();
}

void LocalBook::makeChange( string chapterName, int versionNum, ChangeLine* change ) {
    findChapter( chapterName ).makeChange( versionNum, change );
}

vector<ChangeLine*> LocalBook::getChapterChanges( string chapterName, int versionNum ) {
    return findChapter( chapterName ).getChapterChanges( versionNum );
}

void LocalBook::downgrade( string chapterName, int versionNum ) {
    findChapter( chapterName ).downgrade( versionNum );
}

void LocalBook::setVersionId( string chapterName, int versionNum, int id ) {
    findChapter( chapterName ).setVersionId( versionNum, id );
}

void LocalBook::clear() {
    for (size_t i = 0; i < chapters.size(); i++)
        chapters[i].clear();
    chapters.clear();
    authorsName.clear();
}

list<string> LocalBook::build( string chapterName, int versionNum ) {
    return findChapter( chapterName ).build( versionNum );
}

void LocalBook::setChapterSynced( string chapterName ) {
    findChapter( chapterName ).setSynced();
}

bool LocalBook::isChapterSynced( string chapterName ) {
    return findChapter( chapterName ).isSynced();
}
