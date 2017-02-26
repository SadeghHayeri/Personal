#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <string>

enum color { success, failed, warning };

using namespace std;
class Client;

class Interface {
public:
    Interface( Client& _client ) : client(_client) {};
    void run();

    string getInput( string msg = "[inline]" );
    void showStatus( color status, string msg );

    void menu( color status = success, string msg = "[empty]" );
    void showEditBookMenu( string bookName = "[empty]", color status = success, string msg = "[empty]" );
    void showSignupForm( color status = success, string msg = "[empty]" );
    void showLoginForm( color status = success, string msg = "[empty]" );
    void addBookForm( color status = success, string msg = "[empty]" );
    void firstForm( color status = success, string msg = "[empty]" );
    void editAccess();
    void editBookName( string bookName );

    void addChapter( string bookName );
    void editChapter( string bookName );
    void downgrade();

    void editor( string bookName, string chapterName );
    void versionHistory( string bookName, string chapterName = "[empty]", int versionNum = 0 );

    void download( color status = success, string msg = "[empty]" );
    void sync( string bookName );
    void publish();
    void downloadPublished();

    void requestList();
private:
    Client& client;
};


#endif /* _INTERFACE_H_ */
