#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>
#include "utility.h"

using namespace std;

class Exception {
public:
    Exception( string _name ) : name(_name) {};
    string who() { return name; }
protected:
    string name;
};

class BookExist : public Exception {
public:
    BookExist( string _name ) : Exception(_name) {};
};

class BookNotExist : public Exception {
public:
    BookNotExist( string _name ) : Exception(_name) {};
};

class UserExist : public Exception {
public:
    UserExist( string _name ) : Exception(_name) {};
};

class UserNotExist : public Exception {
public:
    UserNotExist( string _name ) : Exception(_name) {};
};

class ChapterExist : public Exception {
public:
    ChapterExist( string _name ) : Exception(_name) {};
};

class ChapterNotExist : public Exception {
public:
    ChapterNotExist( string _name ) : Exception(_name) {};
};

class VersionNotExist : public Exception {
public:
    VersionNotExist( int versionNum ) : Exception( Utility::to_string(versionNum) ) {};
};

class BadException : public Exception {
public:
    BadException() : Exception( "BadException" ) {};
};

class OldVersion : public Exception {
public:
    OldVersion( int versionNum ) : Exception( Utility::to_string(versionNum) ) {};
};

class NotAccess : public Exception {
public:
    NotAccess( string _name ) : Exception( _name ) {};
};

#endif /* _EXCEPTION_H_ */
