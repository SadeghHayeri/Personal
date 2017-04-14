#include "local_chapter.h"
#include "exception.h"
#include "local_version.h"
#include "edit_line.h"
#include "change_line.h"
#include <algorithm>

void LocalChapter::addNewVersion( int id ) {
    versions.push_back( LocalVersion(id) );
}

int LocalChapter::getLastVersionNum() {
    return versions.size()-1;
}

vector<int> LocalChapter::getVersionList() {
    vector<int> list;
    for (size_t i = 0; i < versions.size(); i++)
        list.push_back( versions[i].getId() );
    return list;
}

void LocalChapter::setVersionId( int versionNum, int id ) {
    findVersion( versionNum ).setId( id );
}

void LocalChapter::makeChange( int versionNum, ChangeLine* change ) {
    if( versionNum != getLastVersionNum() )
        throw OldVersion( versionNum );
    getLastVersion().makeChange( change );
}

LocalVersion& LocalChapter::getLastVersion() {
    return findVersion( getLastVersionNum() );
}

LocalVersion& LocalChapter::findVersion( size_t versionNum ) {
    if( versionNum >= versions.size() )
        throw VersionNotExist( versionNum );

    return versions[versionNum];
}

vector<ChangeLine*> LocalChapter::getChapterChanges( int versionNum ) {
    return findVersion( versionNum ).getChanges();
}

void LocalChapter::downgrade( int versionNum ) {
    if( versionNum > getLastVersionNum() || versionNum < 0 )
        throw VersionNotExist(versionNum);

    versions.erase( versions.begin() + versionNum + 1, versions.end() );
}

void LocalChapter::clear() {
    for (size_t i = 0; i < versions.size(); i++)
        versions[i].clear();
    versions.clear();
    lastBuilds.clear();
}

list<string> LocalChapter::build( int versionNum ) {
    // if( lastBuilds.size() == (size_t)versionNum+1 )
    //     return lastBuilds[versionNum];

    if( versionNum == 0 ) {
        list<string> firstBuild;
        lastBuilds.push_back( firstBuild );
        return firstBuild;
    }

    list<string> lastBuild = build( versionNum-1 );
    vector<ChangeLine*> changes = getChapterChanges( versionNum );
    for (size_t i = 0; i < changes.size(); i++) {
        // addLine
        if( changes[i]->getType() == _AddLine_ ) {
            if( lastBuild.size() < (size_t)changes[i]->getLineNum() )
                throw BadException();

            else {
                ::list<string>::iterator it  = lastBuild.begin();
                for (size_t j = 0; j < (size_t)changes[i]->getLineNum(); j++)
                    ++it;
                lastBuild.insert( it, "" );
            }
        }

        // deleteLine
        if( changes[i]->getType() == _DeleteLine_ ) {
            if( lastBuild.size() < (size_t)changes[i]->getLineNum() )
                throw BadException();
            else {
                ::list<string>::iterator it  = lastBuild.begin();
                for (size_t j = 0; j < (size_t)changes[i]->getLineNum(); j++)
                    ++it;
                lastBuild.erase( it );
            }
        }

        // editLine
        if( changes[i]->getType() == _EditLine_ ) {
            if( lastBuild.size() < (size_t)changes[i]->getLineNum() )
                throw BadException();
            else {
                ::list<string>::iterator it  = lastBuild.begin();
                for (size_t j = 0; j < (size_t)changes[i]->getLineNum(); j++)
                    ++it;
                *it = dynamic_cast<EditLine*>(changes[i])->getText();
            }
        }
    }
    lastBuilds.push_back( lastBuild );
    return lastBuild;

}
