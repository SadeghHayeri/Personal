#ifndef _USER_H_
#define _USER_H_

#include <string>

enum role { _SuperAdmin_, _Admin_, _User_ };

using namespace std;

class User {
public:
    User( string _name, string _password );

    void giveAddBookAccess() { writeBookAccess = true; }
    void setAccess( role _accessLevel ) { accessLevel = _accessLevel; }
    role getRole() { return accessLevel; }

    bool canAddBook() { return writeBookAccess; }
    bool authentication( string _password );
    string getName() { return name; }
private:
    string name;
    size_t password;
    bool writeBookAccess;
    role accessLevel;
};

#endif /* _USER_H_ */
