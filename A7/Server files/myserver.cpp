#include "myserver.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "add_line.h"
#include "delete_line.h"
#include "edit_line.h"
#include "exception.h"
#include "user.h"


string MyServer::cmd( int identifier, string command ) {
try {

    string cmdType;
    stringstream commandLine(command);
    getline( commandLine, cmdType, '|' );

    if( cmdType == "AddUser" ) {

        string userName;
        string password;
        getline( commandLine, userName, '|' );
        getline( commandLine, password, '|' );

        return addUser( userName, password );

    } else if( cmdType == "Login" ) {

        string userName;
        string password;
        getline( commandLine, userName, '|' );
        getline( commandLine, password, '|' );

        if( login(identifier, userName, password) )
            return "Success";
        return "Failed";

    }
    else if( cmdType == "Logout" ) {
        logout( identifier );
        return "Logout";
    }
    else if( cmdType == "AddBook") {

        string bookName;
        vector<string> authors;

        getline( commandLine, bookName, '|' );

        string author;
        while( getline( commandLine, author, '|' ) ) {
            authors.push_back( author );
        }
        return addBook( identifier, bookName, authors );

    }
    else if( cmdType == "AddChapter" ) {

        string bookName;
        string chapterName;
        int place;

        getline( commandLine, bookName, '|' );
        getline( commandLine, chapterName, '|' );
        commandLine >> place;

        return addChapter( identifier, bookName, chapterName, place );

    }
    else if( cmdType == "AddNewVersion" ) {

        string bookName;
        string chapterName;

        getline( commandLine, bookName, '|' );
        getline( commandLine, chapterName, '|' );

        return addNewVersion( identifier, bookName, chapterName );
    }
    else if( cmdType == "GetLastVersionNum" ) {

        string bookName;
        string chapterName;

        getline( commandLine, bookName, '|' );
        getline( commandLine, chapterName, '|' );

        return getLastVersionNum( identifier, bookName, chapterName );
    }
    else if( cmdType == "GetVersionList" ) {

        string bookName;
        string chapterName;

        getline( commandLine, bookName, '|' );
        getline( commandLine, chapterName, '|' );

        return getVersionList( identifier, bookName, chapterName );
    }
    else if( cmdType == "AddLine" ) {

        string bookName;
        string chapterName;
        string versionNumS;
        string lineNumS;

        getline( commandLine, bookName, '|' );
        getline( commandLine, chapterName, '|' );
        getline( commandLine, versionNumS, '|' );
        getline( commandLine, lineNumS, '|' );

        int versionNum = Utility::stoi( versionNumS );
        int lineNum = Utility::stoi( lineNumS );

        return addLine( identifier, bookName, chapterName, versionNum, lineNum );
    }
    else if( cmdType == "DeleteLine" ) {

        string bookName;
        string chapterName;
        string versionNumS;
        string lineNumS;

        getline( commandLine, bookName, '|' );
        getline( commandLine, chapterName, '|' );
        getline( commandLine, versionNumS, '|' );
        getline( commandLine, lineNumS, '|' );

        int versionNum = Utility::stoi( versionNumS );
        int lineNum = Utility::stoi( lineNumS );

        return deleteLine( identifier, bookName, chapterName, versionNum, lineNum );
    }
    else if( cmdType == "EditLine" ) {

        string bookName;
        string chapterName;
        string versionNumS;
        string lineNumS;
        string lineText;

        getline( commandLine, bookName, '|' );
        getline( commandLine, chapterName, '|' );
        getline( commandLine, versionNumS, '|' );
        getline( commandLine, lineNumS, '|' );
        getline( commandLine, lineText, '|' );

        int versionNum = Utility::stoi( versionNumS );
        int lineNum = Utility::stoi( lineNumS );

        return editLine( identifier, bookName, chapterName, versionNum, lineNum, lineText );
    }
    else if( cmdType == "AddBookRequest" ) {
        addBookRequest( identifier );
        return "AddBookRequest";
    }
    else if( cmdType == "GetAccess" ) {

        string userName;
        string accessLevelS;

        getline( commandLine, userName, '|' );
        getline( commandLine, accessLevelS, '|' );
        role accessLevel = ( accessLevelS == "SuperAdmin" )? _SuperAdmin_ : ( accessLevelS == "Admin" ) ? _Admin_ : _User_;

        return setAccess( identifier, userName, accessLevel );
    }
    else if( cmdType == "GetRole" ) {
        return getRole( identifier );
    }
    else if( cmdType == "AddBookRequest" ) {
        addBookRequest( identifier );
        return "AddBookRequest";
    }
    else if( cmdType == "GetRequests" ) {
        return getRequests( identifier );
    }
    else if( cmdType == "GiveAddBookAccess" ) {
        string userName;
        getline( commandLine, userName, '|' );

        return giveAddBookAccess( identifier, userName );
    }
    else if( cmdType == "Downgrade" ) {
        string bookName;
        string chapterName;
        string versionNumS;

        getline( commandLine, bookName, '|' );
        getline( commandLine, chapterName, '|' );
        getline( commandLine, versionNumS, '|' );

        int versionNum = Utility::stoi(versionNumS);

        return downgrade( identifier, bookName, chapterName, versionNum );
    }
    else if( cmdType == "GetChapterChanges" ) {

        string bookName;
        string chapterName;
        string versionNumS;

        getline( commandLine, bookName, '|' );
        getline( commandLine, chapterName, '|' );
        getline( commandLine, versionNumS, '|' );

        int versionNum = Utility::stoi(versionNumS);

        return getChapterChanges( identifier, bookName, chapterName, versionNum );

    }
    else if( cmdType == "GetAuthorsNames" ) {

        string bookName;
        getline( commandLine, bookName, '|' );

        return getAuthorsNames( identifier, bookName );

    }
    else if( cmdType == "GetBookList" ) {
        return getBookList();
    }
    else if( cmdType == "GetPublishedList" ) {
        return getPublishedList();
    }
    else if( cmdType == "GetChapterList" ) {
        string bookName;
        getline( commandLine, bookName, '|' );

        return getChapterList( identifier, bookName );
    }
    else if( cmdType == "PublishBook" ) {
        string bookName;
        getline( commandLine, bookName, '|' );
        return publishBook( identifier, bookName );
    }
    else if( cmdType == "Download" ) {
        string bookName;
        getline( commandLine, bookName, '|' );

        return download( bookName );
    }
    else if( cmdType == "EditBookName" ) {
        string bookName;
        string newName;
        getline( commandLine, bookName, '|' );
        getline( commandLine, newName, '|' );

        return editBookName( identifier, bookName, newName );
    }
    else if( cmdType == "EditAuthors") {
        string bookName;
        vector<string> authors;
        getline( commandLine, bookName, '|' );

        string author;
        while( getline(commandLine, author, '|') )
            authors.push_back( author );

        return editAuthors( identifier, bookName, authors );
    }
    else if( cmdType == "FastUpload" ) {
        string bookName;
        string chapterName;
        string versionNumS;

        string info;
        getline( commandLine, info, '^' );
        stringstream line(info);
        getline( line, bookName, '|' );
        getline( line, chapterName, '|' );
        getline( line, versionNumS, '|' );

        int versionNum = Utility::stoi( versionNumS );

        string changeLine;
        while( getline(commandLine, changeLine, '^') ) {

            stringstream changeStream(changeLine);
            string command;
            getline( changeStream, command, '|' );

            if( command == "EditLine" ) {
                int lineNum;
                string lineText;
                getline( changeStream, lineText, '|' );
                changeStream >> lineNum;
                editLine( identifier, bookName, chapterName, versionNum, lineNum, lineText );
            }
            else if( command == "AddLine" ) {
                int lineNum;
                changeStream >> lineNum;
                addLine( identifier, bookName, chapterName, versionNum, lineNum );
            }
            else if( command == "DeleteLine" ) {
                int lineNum;
                changeStream >> lineNum;
                deleteLine( identifier, bookName, chapterName, versionNum, lineNum );
            }
        }

        return "Success";

    }

    return "Err|BadCommand";

}
catch( BadException ) {
    return "Err|BadException";
    cerr << "Bad exception ocurred!"  << endl;
}
catch(...) {
    return "Err|BadException";
    cerr << "bad catch" << endl;
}

return "Err|BadCommand";

}

void MyServer::saveCmd( int identifier, string command ) {
    log << "cmd saved: " + command;
    Utility::makeFile( "serverFiles.db" );
    Utility::addLineToFile( "serverFiles.db", Utility::to_string( identifier ) + "\t" + command );
}

void MyServer::loadCmds() {

    ifstream file;
    file.open("serverFiles.db");
    vector<int> connectList;

    int id;
    string cmd;
    while( file >> id ) {

        file.ignore();
        getline( file, cmd );

        if( cmd != "Connect" )
            MyServer::cmd( id, cmd );
        else {
            onlineUsers.newConnect( id );
            connectList.push_back(id);
        }

    }

    for (size_t i = 0; i < connectList.size(); i++) {
        onlineUsers.disConnect( connectList[i] );
    }
    log << "cmd loaded from server";

}

string MyServer::editBookName( int identifier, string bookName, string newName ) {
    try {
        db.editBookName( onlineUsers[identifier], bookName, newName );
        log << Utility::to_string(identifier) + " want to edit " + bookName + " name to " + newName;
        return "Success";
    }
    catch( NotAccess ) {
        return "Err|NotAccess";
    }
    catch( BookExist ) {
        return "Err|BookExist";
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }
}

string MyServer::editAuthors( int identifier, string bookName, vector<string> authors ) {
    try {
        db.editAuthors( onlineUsers[identifier], bookName, authors );
        log << Utility::to_string(identifier) + " request for change authros for his book";
        return "Success";
    }
    catch( NotAccess ) {
        return "Err|NotAccess";
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }
    catch( UserNotExist ) {
        return "Err|UserNotExist";
    }
}

string MyServer::getRole( int identifier ) {

    try {
        role a = db.getRole( onlineUsers[identifier] );

        switch (a) {
            case _SuperAdmin_:
                return "SuperAdmin";
                break;
            case _Admin_:
                return "Admin";
                break;
            case _User_:
                return "User";
                break;
        }
        log << Utility::to_string(identifier) + " get his role from server";
        return "Err|BadException";
    }
    catch(...) {
        return "Err|BadException";
    }

}

string MyServer::download( string bookName ) {

    try {
        PublishedBook book = db.download(bookName);

        string result = book.name;
        result += "^";

        result += book.owner;
        result += "^";

        for (size_t i = 0; i < book.authors.size(); i++) {
            result += book.authors[i];
            result += "|";
        }
        result += "^";

        for (size_t i = 0; i < book.chapters.size(); i++) {
            result += book.chapters[i].name;
            result += "|";
            for (size_t j = 0; j < book.chapters[i].lines.size(); j++) {
                result += book.chapters[i].lines[j];
                result += "|";
            }
            result += "^";
        }
        log << bookName + "downloaded from server";
        return result;
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }

}


string MyServer::publishBook( int identifier, string bookName ) {
    try {
        db.publishBook( onlineUsers[ identifier ], bookName );
        log << bookName + " published from " + Utility::to_string(identifier);
        return "success";
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }
    catch( NotAccess ) {
        return "Err|NotAccess";
    }
}

string MyServer::getBookList() {
    vector<string> bookList = db.getBookList();
    string result;
    for (size_t i = 0; i < bookList.size(); i++) {
        result += bookList[i];
        result += "|";
    }
    log << "book list requested";
    return result;
}

string MyServer::getPublishedList() {
    vector<string> bookList = db.getPublishedList();
    string result;
    for (size_t i = 0; i < bookList.size(); i++) {
        result += bookList[i];
        result += "|";
    }
    log << "asked for published list";
    return result;
}

string MyServer::getChapterList( int identifier, string bookName ) {
    try {
        vector<string> chapterList = db.getChapterList( onlineUsers[identifier], bookName );
        string result;
        for (size_t i = 0; i < chapterList.size(); i++) {
            result += chapterList[i];
            result += "|";
        }
        log << Utility::to_string(identifier) + " get chapterList of " + bookName;
        return result;
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }
    catch( NotAccess ) {
        return "Err|NotAccess";
    }
}

string MyServer::getAuthorsNames( int identifier, string bookName ) {
    try {
        vector<User*> authors = db.getAuthors( onlineUsers[identifier], bookName );
        string result;
        for (size_t i = 0; i < authors.size(); i++) {
            result += authors[i]->getName();
            result += "|";
        }
        log << Utility::to_string(identifier) + " get authors name of " + bookName;
        return result;
    }
    catch( NotAccess ) {
        return "Err|NotAccess";
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }
}

string MyServer::getChapterChanges( int identifier, string bookName, string chapterName, int versionNum ) {

    try {

        vector< ChangeLine*> chapterChanges = db.getChapterChanges( onlineUsers[ identifier ], bookName, chapterName, versionNum );

        string result;
        for (size_t i = 0; i < chapterChanges.size(); i++) {

            if( chapterChanges[i]->getType() == _AddLine_ )
                result += "AddLine";
            else if( chapterChanges[i]->getType() == _EditLine_ ) {
                result += "EditLine";
                result += "|";
                result += dynamic_cast<EditLine*>(chapterChanges[i])->getText();
            }
            else if( chapterChanges[i]->getType() == _DeleteLine_ )
                result += "DeleteLine";

            result += "|";
            result += Utility::to_string( chapterChanges[i]->getLineNum() );

            result += "^";
        }

        log << Utility::to_string(identifier) + " get chapter changes of " + bookName + " chapter " + chapterName + " version " + Utility::to_string(versionNum);
        return result;

    }
    catch( NotAccess ) {
        return "Err|NotAccess";
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }
    catch( ChapterNotExist ) {
        return "Err|ChapterNotExist";
    }
    catch( VersionNotExist ) {
        return "Err|VersionNotExist";
    }

}

string MyServer::downgrade( int identifier, string bookName, string chapterName, int versionNum ) {

    try{
        db.downgrade( onlineUsers[identifier], bookName, chapterName, versionNum );
        log << Utility::to_string(identifier) + " downgrade book " << bookName << " chapter " << chapterName << " to " << Utility::to_string(versionNum);
        return "Success";
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }
    catch( ChapterNotExist ) {
        return "Err|ChapterNotExist";
    }
    catch( NotAccess ) {
        return "Err|NotAccess";
    }
    catch( VersionNotExist ) {
        return "Err|VersionNotExist";
    }

}

string MyServer::giveAddBookAccess( int identifier, string userName ) {

    try{
        db.giveAddBookAccess( onlineUsers[ identifier ], userName );
        log << Utility::to_string(identifier) + " add book access to " << userName;
        return "Success";
    }
    catch( NotAccess ) {
        return "Err|NotAccess";
    }
    catch( UserNotExist ) {
        return "Err|UserNotExist";
    }

}

string MyServer::getRequests( int identifier ) {
    try {
        vector< User* > requsetList = db.getRequests( onlineUsers[ identifier ] );
        string requsetListS;
        for (size_t i = 0; i < requsetList.size(); i++) {
            requsetListS += requsetList[i]->getName();
            requsetListS += "|";
        }
        log << Utility::to_string(identifier) + " get requests list";
        return requsetListS;
    }
    catch( NotAccess ) {
        return "Err|NotAccess";
    }
}

string MyServer::setAccess( int identifier, string userName, role accessLevel ) {

    try {
        db.setAccess( onlineUsers[ identifier ], userName, accessLevel );
        log << Utility::to_string(identifier) + " change access " + userName;
        return "Success";
    }
    catch( NotAccess ) {
        return "Err|NotAccess";
    }
    catch( UserNotExist ) {
        return "Err|UserNotExist";
    }

}

void MyServer::addBookRequest( int identifier ) {
    db.addBookRequest( onlineUsers[ identifier ] );
    log << Utility::to_string(identifier) + " add a new request";
}

string MyServer::getLastVersionNum( int identifier, string bookName, string chapterName ) {

    try {
        int v = db.getLastVersionNum( onlineUsers[identifier], bookName, chapterName );
        log << Utility::to_string(identifier) + " get last versionnum ";
        return Utility::to_string( v );
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }
    catch( ChapterNotExist ) {
        return "Err|ChapterNotExist";
    }

}

string MyServer::getVersionList( int identifier, string bookName, string chapterName ) {

    try {
        string result;
        vector<int> list = db.getVersionList( onlineUsers[identifier], bookName, chapterName );
        for (size_t i = 0; i < list.size(); i++) {
            result += Utility::to_string( list[i] );
            result += "|";
        }
        log << Utility::to_string(identifier) + " get version list of " + bookName + " chapter " + chapterName;
        return result;
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }
    catch( ChapterNotExist ) {
        return "Err|ChapterNotExist";
    }

}

string MyServer::addNewVersion( int identifier, string bookName, string chapterName ) {

    try{
        db.addNewVersion( onlineUsers[identifier], bookName, chapterName );
        log << Utility::to_string(identifier) + " add new verion for " + bookName + " chapter " + chapterName;
        return "Success";
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }
    catch( ChapterNotExist ) {
        return "Err|ChapterNotExist";
    }

}

string MyServer::addChapter( int identifier, string bookName, string chapterName, int place ) {

    try{
        db.addChapter( onlineUsers[identifier], bookName, chapterName, place );
        log << Utility::to_string(identifier) + " add a new chapter to " + bookName + " named " + chapterName;
        return "Success";
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }
    catch( ChapterExist ) {
        return "Err|ChapterExist";
    }

}

void MyServer::logout( int identifier ) {
    onlineUsers.logout( identifier );
    log << Utility::to_string(identifier) + " logout";
}

bool MyServer::login( int identifier, string userName, string password ) {

    if( db.authentication(userName, password) ) {
        onlineUsers.login( identifier, db.findUser(userName) );
        log << Utility::to_string(identifier) + " login";
        return true;
    }
    return false;

}

string MyServer::addUser( string userName, string password ) {
    try{
        db.addUser( userName, password );
        log << userName << " signedup";
        return "Success";
    }
    catch( UserExist ) {
        return "Err|UserExist";
    }
}

string MyServer::addBook( int identifier, string bookName, vector<string> authors ) {

    try{
        db.addBook( bookName, onlineUsers[ identifier ], authors );
        log << Utility::to_string(identifier) + " add a new book named " << bookName;
        return "Success";
    }
    catch( NotAccess ) {
        return "Err|NotAccess";
    }
    catch( BookExist ) {
        return "Err|BookExist";
    }
    catch( UserNotExist ) {
        return "Err|UserNotExist";
    }

}

string MyServer::addLine( int identifier, string bookName, string chapterName, int versionNum, int lineNum ) {
    try {
        db.makeChange( onlineUsers[identifier], bookName, chapterName, versionNum, new AddLine( lineNum ) );
        return "Success";
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }
    catch( ChapterNotExist ) {
        return "Err|ChapterNotExist";
    }
    catch( OldVersion ) {
        return "Err|OldVersion";
    }
}
string MyServer::deleteLine( int identifier, string bookName, string chapterName, int versionNum, int lineNum ) {
    try {
        db.makeChange( onlineUsers[identifier], bookName, chapterName, versionNum, new DeleteLine( lineNum ) );
        return "Success";
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }
    catch( ChapterNotExist ) {
        return "Err|ChapterNotExist";
    }
    catch( OldVersion ) {
        return "Err|OldVersion";
    }

}
string MyServer::editLine( int identifier, string bookName, string chapterName, int versionNum, int lineNum, string lineText ) {
    try {
        db.makeChange( onlineUsers[identifier], bookName, chapterName, versionNum, new EditLine( lineNum, lineText ) );
        return "Success";
    }
    catch( BookNotExist ) {
        return "Err|BookNotExist";
    }
    catch( ChapterNotExist ) {
        return "Err|ChapterNotExist";
    }
    catch( OldVersion ) {
        return "Err|OldVersion";
    }

}

///////////////////////////////////////
void MyServer::on_standard_input(string line)
{
  cout << "STDIN: " << line << endl;
  if (line == ":q")
    stop();
}

void MyServer::on_new_connection(int identifier) {
    saveCmd( identifier, "Connect" );
  onlineUsers.newConnect( identifier );
  cout << "new connection (" << identifier << ")" << endl;
}

void MyServer::on_new_message(int identifier, string message) {
    saveCmd( identifier, message );
    string result = cmd( identifier, message );
    // cout << "Input: " << message << endl;
    // cout << "Result: " << result << endl << endl;
    send(identifier, result);
}

void MyServer::on_terminated_connection(int identifier) {
    onlineUsers.disConnect( identifier );
}
