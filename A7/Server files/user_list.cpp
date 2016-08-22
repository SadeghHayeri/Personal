#include "user_list.h"
#include "exception.h"

void UserList::newConnect( int identifier ) {
    disConnect( identifier );
    data newly;
    newly.identifier = identifier;
    newly.login = false;
    list.push_back( newly );
}

void UserList::disConnect( int identifier ) {

    for (size_t i = 0; i < list.size(); i++)
        if( list[i].identifier == identifier ) {
            list.erase( list.begin() + i );
            return;
        }

}

void UserList::login( int identifier, User& user ) {

    for (size_t i = 0; i < list.size(); i++)
        if( list[i].identifier == identifier ) {

            if( list[i].login ) {
                disConnect( i );
                newConnect( i );
            }
            list[i].user = &user;
            list[i].login = true;
            return;

        }

}

void UserList::logout( int identifier ) {

    for (size_t i = 0; i < list.size(); i++)
        if( list[i].identifier == identifier ) {
            list[i].login = false;
            return;
        }

}

User& UserList::operator[]( int index ) {

    for (size_t i = 0; i < list.size(); i++)
        if( list[i].identifier == index ) {
            if( !list[i].login ) {
                throw BadException();
            }
            return *list[i].user;
        }
    throw BadException();

}
