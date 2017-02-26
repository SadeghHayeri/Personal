#include "client.h"
#include <string>
#include "exception.h"
#include "utility.h"
#include "add_line.h"
#include "delete_line.h"
#include "edit_line.h"
#include <sstream>
#include <iostream>
#include "book_maker.h"

//////////////// edit this for next time //////////////////
string Client::send( string command ) {
    socket->send(command);
    return socket->receive();
}
///////////////////////////////////////////////////////////

Client::Client(ClientSocket *_socket )
    : socket(_socket), interface( *this )
{
//    interface.run();
}

void Client::editBookName( string bookName, string newName ) {
    string command = Utility::join( "EditBookName", bookName, newName );
    string result = send( command );
    if( result == "Err|BookNotExist" )
        throw BookNotExist( bookName );
    else if( result == "Err|NotAccess" )
        throw NotAccess( "Client" );
    else if( result == "Err|BookExist" )
        throw BookExist( newName );
}

void Client::editAuthors( string bookName, vector<string> authors ) {

    string command = Utility::join( "EditAuthors", bookName );
    for( size_t i = 0; i < authors.size(); i++ ) {
        command += "|";
        command += authors[i];
    }

    string result = send( command );

    if( result == "Err|BookNotExist" )
        throw BookNotExist( bookName );
    else if( result == "Err|NotAccess" )
        throw NotAccess( "Client" );
    else if( result == "Err|UserNotExist" )
        throw UserNotExist( "author" );

}

vector<string> Client::getPublishedList() {
    string command = "GetPublishedList";
    string result = send( command );

    stringstream line(result);
    vector<string> list;
    string name;
    while( getline(line, name, '|') )
        list.push_back( name );

    return list;
}

void Client::download( string bookName, string fileAddress ) {

    string command = Utility::join( "Download", bookName );

    string result = send( command );
    stringstream line(result);

    PublishedBook book;
    getline( line, book.name, '^' );
    getline( line, book.owner, '^' );

    string authors;
    getline( line, authors, '^' );
    stringstream streamAuthors(authors);
    string author;
    while( getline( streamAuthors, author, '|' ) )
        book.authors.push_back( author );

    string chapter;
    while( getline(line, chapter, '^') ) {
        StringChapter newChapter;
        stringstream streamChapter(chapter);
        getline( streamChapter, newChapter.name, '|' );
        string chapterText;
        while( getline(streamChapter, chapterText, '|') )
            newChapter.lines.push_back( chapterText );
        book.chapters.push_back( newChapter );
    }

    BookMaker::makeHtmlFile( book, fileAddress );

}

vector<ChangeLine*> Client::getChapterChanges( string bookName, string chapterName, int versionNum ) {

    string command = Utility::join( "GetChapterChanges", bookName, chapterName, Utility::to_string(versionNum) );
    string result = send( command );

    if( result == "Err|NotAccess" )
        throw NotAccess( "client" );
    else if( result == "Err|BookNotExist" )
        throw BookNotExist( bookName );
    else if( result == "Err|ChapterNotExist" )
        throw ChapterNotExist( chapterName );
    else if( result == "Err|VersionNotExist" )
        throw VersionNotExist( versionNum );

    else {
        vector<ChangeLine*> chapterChanges;

        stringstream line(result);
        string changeLine;

        while( getline(line, changeLine, '^') ) {

            stringstream changeStream(changeLine);
            string command;
            getline( changeStream, command, '|' );

            if( command == "EditLine" ) {
                int lineNum;
                string lineText;
                getline( changeStream, lineText, '|' );
                changeStream >> lineNum;
                chapterChanges.push_back( new EditLine(lineNum, lineText) );
            }
            else if( command == "AddLine" ) {
                int lineNum;
                changeStream >> lineNum;
                chapterChanges.push_back( new AddLine(lineNum) );
            }
            else if( command == "DeleteLine" ) {
                int lineNum;
                changeStream >> lineNum;
                chapterChanges.push_back( new DeleteLine(lineNum) );
            }
        }

        return chapterChanges;
    }

}

vector<string> Client::getBookList() {
    string command = "GetBookList";
    string result = send( command );
    stringstream line(result);

    vector<string> bookList;
    string bookName;
    while ( getline( line, bookName, '|') )
        bookList.push_back( bookName );
    return bookList;
}

vector<string> Client::getChapterList( string bookName ) {
    string command = Utility::join( "GetChapterList", bookName );

    string result = send( command );
    if( result == "Err|BookNotExist" )
        throw BookNotExist(bookName);
    else if( result == "Err|NotAccess" )
        throw NotAccess( "client" );

    stringstream line(result);
    vector<string> chapterList;
    string chapterName;
    while ( getline( line, chapterName, '|') )
        chapterList.push_back( chapterName );
    return chapterList;
}

vector<int> Client::getVersionList( string bookName, string chapterName ) {
    string command = Utility::join( "GetVersionList", bookName, chapterName );

    string result = send( command );

    if( result == "Err|BookNotExist" )
        throw BookNotExist( bookName );
    else if( result == "Err|ChapterNotExist" )
        throw ChapterNotExist( chapterName );

    vector<int> list;
    stringstream line(result);
    string id;
    while ( getline(line, id, '|') )
        list.push_back( Utility::stoi(id) );
    return list;

}

void Client::publishBook( string bookName ) {
    string command = Utility::join( "PublishBook", bookName );
    string result = send( command );

    if( result == "Err|BookNotExist" )
        throw BookNotExist( bookName );
    else if( result == "Err|NotAccess" )
        throw NotAccess( "client" );

}

void Client::downgrade( string bookName, string chapterName, int versionNum ) {
    string command = Utility::join( "Downgrade", bookName, chapterName, Utility::to_string(versionNum) );
    string result = send( command );

    if( result == "Err|BookNotExist" )
        throw BookNotExist( bookName );
    else if( result == "Err|ChapterNotExist" )
        throw ChapterNotExist( chapterName );
    else if( result == "Err|NotAccess" )
        throw NotAccess( "client" );
    else if( result == "Err|VersionNotExist" )
        throw VersionNotExist(versionNum);
}

void Client::setAccess( string userName, role accessLevel ) {

    string accessLevelS = (accessLevel==_User_)? "User" : (accessLevel==_Admin_)? "Admin" : "SuperAdmin";
    string command = Utility::join( "GetAccess", userName, accessLevelS );
    string result = send( command );

    if( result == "Err|NotAccess" )
        throw NotAccess( "client" );
    else if( result == "Err|UserNotExist" )
        throw UserNotExist( userName );
}

void Client::giveAddBookAccess( string userName ) {
    string command = Utility::join( "GiveAddBookAccess", userName );
    string result = send( command );

    if( result == "Err|NotAccess" )
        throw NotAccess( "client" );
    else if( result == "Err|UserNotExist" )
        throw UserNotExist( userName );
}

void Client::addBookRequest() {
    string command = "AddBookRequest";
    send( command );
}

vector< string > Client::getRequests() {

    string command = "GetRequests";
    string resultS = send( command );

    if( resultS == "Err|NotAccess" )
        throw NotAccess( "only admin" );

    stringstream line(resultS);
    vector< string > result;
    string userName;
    while( getline(line, userName, '|') ) {
        result.push_back( userName );
    }
    return result;

}

void Client::addLine( string bookName, string chapterName, int versionNum, int lineNum ) {

    string command = Utility::join( "AddLine", bookName, chapterName, Utility::to_string(versionNum), Utility::to_string(lineNum) );
    string result = send( command );

    if( result == "Err|BookNotExist" )
        throw BookNotExist( bookName );
    else if( result == "Err|ChapterNotExist" )
        throw ChapterNotExist( chapterName );
    else if( result == "Err|OldVersion" )
        throw OldVersion( versionNum );

}

void Client::deleteLine( string bookName, string chapterName, int versionNum, int lineNum ) {

    string command = Utility::join( "DeleteLine", bookName, chapterName, Utility::to_string(versionNum), Utility::to_string(lineNum) );
    string result = send( command );

    if( result == "Err|BookNotExist" )
        throw BookNotExist( bookName );
    else if( result == "Err|ChapterNotExist" )
        throw ChapterNotExist( chapterName );
    else if( result == "Err|OldVersion" )
        throw OldVersion( versionNum );

}
void Client::editLine( string bookName, string chapterName, int versionNum, int lineNum, string lineText ) {

    string command = Utility::join( "EditLine", bookName, chapterName, Utility::to_string(versionNum), Utility::to_string(lineNum), lineText );
    string result = send( command );

    if( result == "Err|BookNotExist" )
        throw BookNotExist( bookName );
    else if( result == "Err|ChapterNotExist" )
        throw ChapterNotExist( chapterName );
    else if( result == "Err|OldVersion" )
        throw OldVersion( versionNum );
}


role Client::getRole() {
    string command = "GetRole";

    string result = send( command );

    if( result == "SuperAdmin" )
        return _SuperAdmin_;
    else if( result == "Admin" )
        return _Admin_;
    else if( result == "User" )
        return _User_;

    throw BadException();
}


int Client::getLastVersionNum( string bookName, string chapterName ) {

    string command =  Utility::join( "GetLastVersionNum", bookName, chapterName );
    string result = send( command );

    if( result == "Err|BookNotExist" )
        throw BookNotExist( bookName );
    else if( result == "Err|ChapterNotExist" )
        throw ChapterNotExist( chapterName );

    return Utility::stoi( result );

}

void Client::addNewVersion( string bookName, string chapterName ) {

    string command = Utility::join( "AddNewVersion", bookName, chapterName );
    string result = send( command );

    if( result == "Err|BookNotExist" )
        throw BookNotExist( bookName );
    else if( result == "Err|ChapterNotExist" )
        throw ChapterNotExist( chapterName );

}

void Client::signUp( string userName, string password ) {

    string command = Utility::join( "AddUser", userName, password );
    string result = send( command );

    if( result == "Err|UserExist" ) {
        throw UserExist( userName );
    }
    else if( result == "BadErr" || result == "BadCommand" )
        throw BadException();

}

bool Client::login( string userName, string password ) {

    string command = Utility::join( "Login", userName, password );
    string result = send( command );

    if( result == "Success" )
        return true;

    // Failed
    return false;

}

void Client::logout() {

    string command = "Logout";
    string result = send( command );

    if( result != "Logout" )
        throw BadException();

    repo.clear();

}

void Client::addBook( string bookName, vector<string> authors ) {

    string command = Utility::join( "AddBook", bookName );
    command += "|";
    for (size_t i = 0; i < authors.size(); i++) {
        command += authors[i];
        command += "|";
    }

    string result = send( command );

    if( result == "Err|BookExist" )
        throw BookExist( bookName );
    else if( result == "Err|UserNotExist")
        throw UserNotExist( "unknow" );
    else if( result == "Err|NotAccess" )
        throw NotAccess( "unknow" );

}

void Client::addChapter( string bookName, string chapterName, int place ) {

    string command = Utility::join( "AddChapter", bookName, chapterName, Utility::to_string( place ) );
    string result = send( command );

    if( result == "Err|BookNotExist" )
        throw BookNotExist( bookName );
    else if ( result == "Err|ChapterExist" )
        throw ChapterExist( chapterName );

}

vector< string > Client::getAuthorsNames( string bookName ) {

    string command = Utility::join( "GetAuthorsNames", bookName );
    string result = send( command );

    stringstream line(result);
    vector<string> authors;
    string author;
    while ( getline(line, author) ) {
        authors.push_back( author );
    }
    return authors;
}

//////////////////////////////////////////////////////////////////////////////
void Client::syncBook( string bookName ) {
    if( !repo.isBookSynced( bookName ) ) {
        vector<string> authorsNames = repo.getAuthorsNames( bookName );
        addBook( bookName, authorsNames );
        repo.setBookSynced( bookName );
    }
}

void Client::syncChapter( string bookName, string chapterName ) {
    if( !repo.isBookSynced(bookName) )
        syncBook( bookName );
    if( !repo.isChapterSynced(bookName, chapterName) ) {
        addChapter( bookName, chapterName );
        repo.setChapterSynced(bookName, chapterName);
    }
}

void Client::syncVersion( string bookName, string chapterName, int versionNum ) {

    if( !repo.isBookSynced(bookName) )
        syncBook( bookName );
    if( !repo.isChapterSynced(bookName, chapterName) )
        syncChapter( bookName, chapterName );

    vector<int> versionList = getVersionList( bookName, chapterName );
    vector<int> localVersionList = repo.getVersionList( bookName, chapterName );

    // if user dont want to sync all versions
    localVersionList.erase( localVersionList.begin()+versionNum + 1, localVersionList.end() );

    size_t lastVersionNum = versionList.size();
    size_t lastLocalVersionNum = localVersionList.size();

    if( versionList.size() > localVersionList.size() )
        throw( OldVersion(localVersionList.size()) );

    for (size_t i = 0; i < versionList.size(); i++) {
        if( localVersionList[i] != versionList[i] )
            throw( OldVersion(i) );
    }

    // this code add changed version to server
    for (size_t i = lastVersionNum; i < lastLocalVersionNum; i++) {

        // get changes
        vector<ChangeLine*> changes = repo.getChapterChanges(bookName, chapterName, i);

        // add a new version for them
        addNewVersion( bookName, chapterName );
        int last = getLastVersionNum( bookName, chapterName );

////////// old and slow upload /////////////////////////////////////////////////////////////////////////
//        // add changes to server
//        for (size_t i = 0; i < changes.size(); i++) {
//            if( changes[i]->getType() == _AddLine_ )
//                addLine( bookName, chapterName, last, changes[i]->getLineNum() );
//            else if( changes[i]->getType() == _DeleteLine_ )
//                deleteLine( bookName, chapterName, last, changes[i]->getLineNum() );
//            else
//                editLine( bookName, chapterName, last, changes[i]->getLineNum(), dynamic_cast<EditLine*>(changes[i])->getText() );
//        }
////////////////////////////////////////////////////////////////////////////////////////////////////////

///////// fast upload ///////////////////////////////////////////////////////////////////////////////////

        string command = Utility::join( "FastUpload", bookName, chapterName, Utility::to_string(i) );
        command += "^";
        for (size_t i = 0; i < changes.size(); i++) {

            if( changes[i]->getType() == _AddLine_ )
                command += "AddLine";
            else if( changes[i]->getType() == _EditLine_ ) {
                command += "EditLine";
                command += "|";
                command += dynamic_cast<EditLine*>(changes[i])->getText();
            }
            else if( changes[i]->getType() == _DeleteLine_ )
                command += "DeleteLine";

            command += "|";
            command += Utility::to_string( changes[i]->getLineNum() );

            command += "^";
        }

        string result = send( command );

        if( result == "Err|BookNotExist" )
            throw BookNotExist( bookName );
        else if( result == "Err|ChapterNotExist" )
            throw ChapterNotExist( chapterName );
        else if( result == "Err|OldVersion" )
            throw OldVersion( versionNum );

//////////////////////////////////////////////////////////////////////////////////////////////////////////


    }

    // update local versions id
    vector<int> newVersionList = getVersionList( bookName, chapterName );
    for (size_t i = versionList.size(); i < localVersionList.size(); i++) {
        repo.setVersionId( bookName, chapterName, i, newVersionList[i] );
    }

}

//////////////////////////////////////////////////////////////////////////////
void Client::downloadLastVersion( string bookName, string chapterName ) {

    if( !repo.chapterExist(bookName, chapterName) ) {

        // add book if does not exist
        if( !repo.bookExist(bookName) ) {
            repo.addBook( bookName, getAuthorsNames(bookName) );
            repo.setBookSynced( bookName );
        }

        // add chapter if does not exist
        if( !repo.chapterExist(bookName, chapterName) ) {
            repo.addChapter( bookName, chapterName );
            repo.setChapterSynced( bookName, chapterName );
        }

    }

    vector<int> versionList = getVersionList( bookName, chapterName );
    vector<int> localVersionList = repo.getVersionList( bookName, chapterName );

    for (size_t i = 1; i < versionList.size(); i++) {

        if( localVersionList.size() > i ) {
            if( versionList[i] != localVersionList[i] ) {
                repo.downgrade( bookName, chapterName, i-1 );
                downloadVersion( bookName, chapterName, i, versionList[i] );
            }
        }
        else {
            downloadVersion( bookName, chapterName, i, versionList[i] );
        }

    }
     repo.downgrade( bookName, chapterName, versionList.size()-1 );

}

void Client::downloadVersion( string bookName, string chapterName, int versionNum, int id ) {

    // download changes and add to new book
    vector<ChangeLine*> ch = getChapterChanges( bookName, chapterName, versionNum );

    // add a new version( for first time, this version already exist )
    if( versionNum != 0 ) {
        repo.addNewVersion(bookName, chapterName, id);
    }

    // import changes to repository
    for (size_t i = 0; i < ch.size(); i++)
        repo.makeChange( bookName, chapterName, versionNum, ch[i] );

}

list<string> Client::build( string bookName, string chapterName, int versionNum ) {
    return repo.build( bookName, chapterName, versionNum );
}

