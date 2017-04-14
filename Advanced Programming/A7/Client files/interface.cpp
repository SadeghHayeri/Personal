#include "interface.h"
#include "client.h"
#include "colormod.h"
#include "utility.h"
#include <iostream>
#include "exception.h"
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <list>
#include <fstream>

////////////// colors /////////////////
Color::Modifier org(Color::FG_ORG);
Color::Modifier def(Color::FG_DEFAULT);
Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
///////////////////////////////////////

void Interface::run() {
    firstForm();
}

void Interface::firstForm( color status, string msg ) {
    Utility::clear();
    cout << "- Login or Signup -" << endl;
    showStatus( status, msg);

    while( true ) {

        string command = getInput();

        if( command == "q" ) {
            Utility::clear();
            exit( 0 );
        }

        else if( command == "help" ) {
            /////////////.........
        }

        else if( command == "signup" ) {
            showSignupForm();
            firstForm( success, "signup success ✓" );
        }

        else if( command == "login" )
            showLoginForm();

        else {
            cout << red << "Bad command, insert 'help' for more information!" << def << endl;
        }

    }
}

void Interface::showStatus( color status, string msg ) {
    if( msg != "[empty]" ) {
        if ( status == success ) {
            cout << green << msg << def << endl;
        }
        else if( status == failed ) {
            cout << red << msg << def << endl;
        }
        else if( status == warning ) {
            cout << org << msg << def << endl;
        }
    }
    cout << endl;
}

void Interface::menu( color status, string msg ) {
    Utility::clear();
    cout << "- Main Menu -" << endl;
    showStatus( status, msg);

    try{
        while( true ) {

            string command = getInput();

            if( command == "logout" || command == "q" ) {
                client.logout();
                firstForm( success, "logout ✓" );
            }

            else if( command == "help" ) {
                ///////////........
            }

            else if( command == "download" ) {
                download();
            }

            else if( command == "downgrade" ) {
                downgrade();
            }

            else if( command == "addbook" ) {
                addBookForm();
                menu( success, "book added ✓" );
            }

            else if( command == "editbook") {
                showEditBookMenu();
                firstForm( success, "success ✓" );
            }
            else if( command == "sendrequest" ) {
                client.addBookRequest();
                menu( success, "request sended ✓" );
            }
            else if( command == "requestlist" ) {
                requestList();
            }
            else if( command == "editaccess" ) {
                editAccess();
            }
            else if( command == "publish" ) {
                publish();
            }
            else if( command == "downloadbook") {
                downloadPublished();
            }
            else {
                cout << red << "Bad command, insert 'help' for more information!" << def << endl;
            }

        }
    }
    catch( NotAccess ) {
        menu( failed, "not access, try another way!" );
    }
    catch( BookExist ) {
        menu( failed, "this book exist, use other name for it!" );
    }
    catch( ChapterExist ) {
        menu( failed, "this chapter exist, user other name!" );
    }
    catch( BookNotExist ex ) {
        menu( failed, "cant find this book named " + ex.who() );
    }
    catch( ChapterNotExist ex ) {
        menu( failed, "cant find this chapter named " + ex.who() );
    }
    catch( UserNotExist ) {
        menu( failed, "user not found!" );
    }
    catch( VersionNotExist ) {
        menu( failed, "cant find this version!" );
    }
    catch( OldVersion ) {
        menu( failed, "this version already exist :/" );
    }
    catch( BadException ) {
        menu( failed, "BAD EXCEPTION :]" );
    }
}

void Interface::downloadPublished() {
    vector<string> list = client.getPublishedList();
    for (size_t i = 0; i < list.size(); i++)
        cout << def << "-" << org << list[i] << def << endl;

    string bookName = getInput( "which one ?" );
    cout << org << "downloading..." << def << endl;
    client.download(bookName);
    menu( success, "download complite, see library folder ✓" );

}

void Interface::publish() {
    Utility::clear();
    cout << "- Publish -" << endl << endl;

    vector<string> serverBookList = client.getBookList();
    if( serverBookList.empty() )
        menu( failed, "no book to publish!" );

    for (size_t i = 0; i < serverBookList.size(); i++)
        cout << "-" << org << serverBookList[i] << def << endl;

    string bookName = getInput( "which one ?" );

    cout << org << "publishing..." << def << endl;
    client.publishBook( bookName );
    menu( success, "book published ✓" );
}

void Interface::editAccess() {
    Utility::clear();
    cout << "- EditAccess -" << endl;

    string userName = getInput( "who?" );
    string accessLevelS = getInput( "superadmin - admin - user ?" );

    role accessLevel = ( accessLevelS == "superadmin" )? _SuperAdmin_ : ( accessLevelS == "admin" ) ? _Admin_ : _User_;
    client.setAccess( userName, accessLevel );
    menu( success, "access changed ✓");
}


void Interface::requestList() {
    Utility::clear();
    cout << "- RequestList -" << endl;

    vector<string> list = client.getRequests();
    if( list.empty() )
        menu( failed, "list empty!" );

    for (size_t i = 0; i < list.size(); i++)
        cout << org << list[i] << def << endl;

    string command = getInput( "who want to confirm?" );
    client.giveAddBookAccess( command );
    menu( success, "request confirm ✓");
}

void Interface::addBookForm( color status, string msg ) {
    Utility::clear();
    cout << "- AddBook -" << endl;
    showStatus( status, msg);

    string bookName = getInput( "insert book name:");
    string authorsNames = getInput( "insert book authors ( example: 'sadegh|ali|reza' )");

    stringstream line(authorsNames);
    vector<string> authors;
    string author;
    while ( getline(line, author) ) {
        authors.push_back( author );
    }
    client.addLocalBook( bookName, authors );
}

string Interface::getInput( string msg ) {
    cout << def;
    if( msg != "[inline]" ) {
        cout << msg << endl;
    }
    cout << "> " << green;
    string input;
    getline( cin, input );
    cout << def;
    return input;
}

void Interface::showEditBookMenu( string bookName, color status, string msg ) {
    Utility::clear();
    cout << "- Edit Book -" << endl;
    if( bookName != "[empty]" )
    cout << "-" << org << bookName << def << "-" << endl;
    showStatus( status, msg);

    if( bookName == "[empty]" ) {

        vector<string> localBookList = client.getLocalBookList();
        if( localBookList.empty() )
            menu( failed, "no book to edit, first create new book!" );

        for (size_t i = 0; i < localBookList.size(); i++)
            cout << "-" << org << localBookList[i] << def << endl;

        // get book name
        bookName = getInput( "which one ?" );
        showEditBookMenu( bookName, status, msg );
    }

    while ( true ) {
        string command = getInput( "what do you want to do ?" );

        if( command == "q" )
            menu();
        else if( command == "help" ) {
            cout << "'q'\tfor exist bookEdit" << endl;
            cout << "'help'\tto show this message" << endl;
            cout << "'addchapter'\tfor add a new chapter to book" << endl;
            cout << "'editchapter'\tto edit chapter" << endl;
        }
        else if( command == "addchapter" ) {
            addChapter( bookName );
        }
        else if( command == "editchapter" ) {
            editChapter( bookName );
        }
        else if( command == "sync" ) {
            sync( bookName );
        }
        else if( command == "history" ) {
            versionHistory( bookName );
        }
        else if( command == "editname" ) {
            editBookName(bookName);
        }
    }

}

void Interface::editBookName( string bookName ) {
    Utility::clear();
    cout << "- EditName -" << endl;
    cout << "-" << org << bookName << def << "-" << endl << endl;

    string newName = getInput( "please enter newname" );
    client.editBookName( bookName, newName );
    client.editLocalBookName( bookName, newName );
    showEditBookMenu( newName, success, "name edited ✓" );

}

void Interface::versionHistory( string bookName, string chapterName, int versionNum ) {
    Utility::clear();
    cout << "- VersionHistory -" << endl;

    if( chapterName == "[empty]" ) {
        cout << "-" << org << bookName << def << "-" << endl << endl;

        vector<string> chapterList = client.getLocalChapterList( bookName );
        if( chapterList.empty() )
            showEditBookMenu( bookName, failed, "no chapter to edit, first add a new chapter!" );
        for (size_t i = 0; i < chapterList.size(); i++)
            cout << "-" << org << chapterList[i] << def << endl;

        // get name
        string chapterName = getInput( "which one ?" );
        versionHistory( bookName, chapterName, client.getLocalLastVersionNum(bookName, chapterName) );
    }
    else {
        cout << "-> " << org << bookName << def << "-> " << org << chapterName << def << "-> " << org << "v " << versionNum << endl << endl;
        // show chapter
        Utility::clear();
        list<string> chapter = client.build( bookName, chapterName, versionNum );
        ::list<string>::iterator it = chapter.begin();
        for (size_t i = 0; i < chapter.size(); i++) {
            cout << org << i << string( Utility::to_string(chapter.size()).size() - Utility::to_string(i).size(), ' ' ) << "| " << def << *it << endl;
            ++it;
        }

        string command = getInput( "'n' for nextVersion - 'p' for previousVersion - 'q' for exit" );

        if( command == "n" ) {
            if( versionNum != client.getLocalLastVersionNum(bookName, chapterName) )
                versionHistory( bookName, chapterName, versionNum+1 );
        }
        else if( command == "p" ) {
            if( versionNum != 0 )
                versionHistory( bookName, chapterName, versionNum-1 );
        }
        else if( command == "q" ) {
            showEditBookMenu( bookName );
        }
        else
            versionHistory( bookName, chapterName, versionNum );

    }

}

void Interface::downgrade() {
    Utility::clear();
    cout << "- Downgrade -" << endl;

    string type = getInput( "online or local?" );

    if( type == "local" ) {
        vector<string> bookList = client.getLocalBookList();
        if( bookList.empty() )
            menu( failed, "no book to edit, first add a new chapter!" );
        for (size_t i = 0; i < bookList.size(); i++)
            cout << "-" << org << bookList[i] << def << endl;
        string bookName = getInput( "which book?" );

        vector<string> chapterList = client.getLocalChapterList( bookName );
        if( chapterList.empty() )
            menu( failed, "no chapter to edit, first add a new chapter!" );
        for (size_t i = 0; i < chapterList.size(); i++)
            cout << "-" << org << chapterList[i] << def << endl;
        string chapterName = getInput( "which chapter?" );

        int lastVersionNum = client.getLocalLastVersionNum( bookName, chapterName );
        cout << "last version is " << lastVersionNum << endl;

        string versionS = getInput( "what version you want to downgrade!" );
        int version = Utility::stoi(versionS);

        client.LocalDowngrade(bookName, chapterName, version);

    }
    else if( type == "online" ) {
        vector<string> bookList = client.getBookList();
        if( bookList.empty() )
            menu( failed, "no book to edit, first add a new chapter!" );
        for (size_t i = 0; i < bookList.size(); i++)
            cout << "-" << org << bookList[i] << def << endl;
        string bookName = getInput( "which book?" );

        vector<string> chapterList = client.getChapterList( bookName );
        if( chapterList.empty() )
            menu( failed, "no chapter to edit, first add a new chapter!" );
        for (size_t i = 0; i < chapterList.size(); i++)
            cout << "-" << org << chapterList[i] << def << endl;
        string chapterName = getInput( "which chapter?" );

        int lastVersionNum = client.getLastVersionNum( bookName, chapterName );
        cout << "last version is " << lastVersionNum << endl;

        string versionS = getInput( "what version you want to downgrade!" );
        int version = Utility::stoi(versionS);

        client.downgrade(bookName, chapterName, version);
        try{
            client.LocalDowngrade(bookName, chapterName, version);
        }
        catch(...) {
            // ok do nothing! :D
        }

    }
    menu( success, "downgrade complite ✓");
}

void Interface::sync( string bookName ) {
    Utility::clear();
    cout << "- Sync -" << endl;
    cout << "-" << org << bookName << def << "-" << endl << endl;

    vector<string> chapterList = client.getLocalChapterList( bookName );
    if( chapterList.empty() )
        showEditBookMenu( bookName, failed, "no chapter to edit, first add a new chapter!" );
    for (size_t i = 0; i < chapterList.size(); i++)
        cout << "-" << org << chapterList[i] << def << endl;

    string chapterName = getInput( "which chapter you want to sync to server?" );
    string command = getInput( "how far sync you want to do?" );
    if( command == "all" )
        command = Utility::to_string( client.getLocalLastVersionNum(bookName, chapterName) );

    cout << org << "syncing..." << def << endl;
    client.syncVersion( bookName, chapterName, Utility::stoi(command) );
    showEditBookMenu(bookName, success, "book synced ✓");
}

void Interface::download( color status, string msg ) {
    Utility::clear();
    cout << "- Download -" << endl;
    showStatus( status, msg);

    vector<string> serverBookList = client.getBookList();
    if( serverBookList.empty() )
        menu( failed, "no book to download!" );

    for (size_t i = 0; i < serverBookList.size(); i++)
        cout << "-" << org << serverBookList[i] << def << endl;

    string bookName = getInput( "which one ?" );

    Utility::clear();
    cout << "- Download -" << endl;

    vector<string> chapterList = client.getChapterList(bookName);
    if( chapterList.empty() )
        menu( failed, "no chapter to download!" );

    for (size_t i = 0; i < chapterList.size(); i++)
        cout << "-" << org << chapterList[i] << def << endl;

    string chapterName = getInput( "which one ?" );

    client.downloadLastVersion( bookName, chapterName );

    menu( success, "download complite ✓" );

}

void Interface::editChapter( string bookName ) {
    Utility::clear();
    cout << "- EditChapter -" << endl;
    cout << "-" << org << bookName << def << "-" << endl << endl;

    vector<string> chapterList = client.getLocalChapterList( bookName );
    if( chapterList.empty() )
        showEditBookMenu( bookName, failed, "no chapter to edit, first add a new chapter!" );
    for (size_t i = 0; i < chapterList.size(); i++)
        cout << "-" << org << chapterList[i] << def << endl;

    // get name
    string chapterName = getInput( "which one ?" );

    // add a new version for it
    client.addLocalNewVersion( bookName, chapterName );

    // enter editor
    editor( bookName, chapterName );
}

void Interface::editor( string bookName, string chapterName ) {
    // show chapter
    Utility::clear();
    int lastVersionNum = client.getLocalLastVersionNum( bookName, chapterName );
    cout << "-Edit-" << endl;
    cout << "-" << org << bookName << def << "-" << org << chapterName << def << "-" << org << "version " << lastVersionNum << def << "-" << endl << endl;
    list<string> chapter = client.build( bookName, chapterName, lastVersionNum );

    ::list<string>::iterator it = chapter.begin();
    for (size_t i = 0; i < chapter.size(); i++) {
        cout << org << i << string( Utility::to_string(chapter.size()).size() - Utility::to_string(i).size(), ' ' ) << "| " << def << *it << endl;
        ++it;
    }

    while( true ) {
        string command = getInput();

        stringstream line(command);
        string cmdType;
        line >> cmdType;
        if( cmdType == "q" )
            showEditBookMenu( bookName );
        if( cmdType == "addline" ) {
            int lineNum;
            line >> lineNum;
            client.addLocalLine(bookName, chapterName, lastVersionNum, lineNum);
            editor( bookName, chapterName );
        }
        else if( cmdType == "deleteline" ) {
            int lineNum;
            line >> lineNum;
            client.deleteLocalLine(bookName, chapterName, lastVersionNum, lineNum);
            editor( bookName, chapterName );
        }
        else if( cmdType == "editline" ) {
            int lineNum;
            string txt;
            line >> lineNum;
            getline( line, txt );
            client.editLocalLine(bookName, chapterName, lastVersionNum, lineNum, txt);
            editor( bookName, chapterName );
        }
        else if( cmdType == "input" ) {
            string fileAddress;
            line >> fileAddress;
            ifstream file;
            cout << org << "importing file..." << def << endl;
            file.open( fileAddress.c_str() );
            if( file ) {
                string fileLine;
                int lineNum = 0;
                while ( getline(file, fileLine) ) {
                    client.addLocalLine(bookName, chapterName, lastVersionNum, lineNum);
                    client.editLocalLine(bookName, chapterName, lastVersionNum, lineNum, fileLine);
                    lineNum++;
                }
            }
            else {
                cout << red << "file not found" << endl;
            }
            editor( bookName, chapterName );
        }
        else
            cout << red << "BadCommand" << def << endl;
    }
}

void Interface::addChapter( string bookName ) {
    Utility::clear();
    cout << "- AddChapter -" << endl;
    cout << "-" << org << bookName << def << "-" << endl << endl;

    string chapterName = getInput( "please insert a name for new chapter:" );
    string command = getInput( "do you want to replace specific to that allocation? [y/n]");
    if( command == "y" ) {
        string placeS = getInput("insert where do you want to replace for it?");
        int place = Utility::stoi(placeS);
        client.addLocalChapter(bookName, chapterName, place);
    }
    else
        client.addLocalChapter(bookName, chapterName);

    showEditBookMenu( bookName, success, "added ✓" );
}

void Interface::showSignupForm( color status, string msg ) {
    try {
        Utility::clear();
        cout << "- SignUp -" << endl;
        showStatus( status, msg);

        string username = getInput( "please insert a username:" );
        string password = getInput( "please insert a password:" );
        client.signUp( username, password );
    }
    catch( UserExist ) {
        showSignupForm( failed, "this username already exist, please use another username" );
    }
}

void Interface::showLoginForm( color status, string msg ) {
    Utility::clear();
    cout << "- Login -" << endl;
    showStatus( status, msg);

    string username = getInput( "username:" );
    string password = getInput( "password:" );

    if( client.login(username, password) ) {
        menu( success, "login success ✓" );
    }
    else {
        firstForm( failed, "username or password incorrect, try again" );
    }
}
