#ifndef _USER_LIST_H_
#define _USER_LIST_H_

#include "user.h"
#include <vector>

struct data {
    User* user;
    int identifier;
    bool login;
};

using namespace std;

class UserList {
public:
    void newConnect( int identifier );
    void disConnect( int identifier );
    void login( int identifier, User& user );
    void logout( int identifier );
    User& operator[]( int index );
private:
    vector< data > list;
};

#endif /* _USER_LIST_H_ */
