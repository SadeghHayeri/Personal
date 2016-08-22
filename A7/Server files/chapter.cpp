#include "chapter.h"
#include "exception.h"
#include "edit_line.h"
#include "change_line.h"

void Chapter::addNewVersion() {
    versions.push_back( Version(versions.size(), versionCounter) );
    versionCounter++;
}

Version& Chapter::findVersion( size_t versionNum ) {

    if( versionNum >= versions.size() )
        throw VersionNotExist( versionNum );

    return versions[versionNum];

}

int Chapter::getLastVersionNum() {
    return versions.size()-1;
}

vector<int> Chapter::getVersionList() {
    vector<int> list;
    for (size_t i = 0; i < versions.size(); i++)
        list.push_back( versions[i].getId() );
    return list;
}

void Chapter::downgrade( int versionNum ) {

    if( versionNum > getLastVersionNum() || versionNum < 0 )
        throw VersionNotExist(versionNum);

    versions.erase( versions.begin() + versionNum + 1, versions.end() );

}

Version& Chapter::getLastVersion() {
    return findVersion( getLastVersionNum() );
}

void Chapter::makeChange( int versionNum, ChangeLine* change ) {
    if( versionNum != getLastVersionNum() )
        throw OldVersion( versionNum );
    getLastVersion().makeChange( change );
}


vector<ChangeLine*> Chapter::getChapterChanges( int versionNum ) {
    return findVersion( versionNum ).getChanges();
}

list<string> Chapter::build( int versionNum ) {

    if( versionNum == 0 ) {
        list<string> firstBuild;
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
    return lastBuild;

}

void Chapter::clear() {
    for (size_t i = 0; i < versions.size(); i++)
        versions[i].clear();
    versions.clear();
}
