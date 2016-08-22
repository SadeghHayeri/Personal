#include "user.h"
#include "utility.h"

User::User( string _name, string _password ) {
    name = _name;
    password = Utility::hash( _password );
    writeBookAccess = false;
    accessLevel = _User_;
}

bool User::authentication( string _password ) {
    return password == Utility::hash(_password);
}
