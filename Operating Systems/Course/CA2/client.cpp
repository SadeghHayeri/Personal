/*
** client.c -- a stream socket client demo
*/

#include <iostream>
#include <unistd.h>
#include "network.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr,"usage: client hostname port\n");
        exit(1);
    }
    char* hostname = argv[1];
    char* port = argv[2];

    int socket_fd = create_socket_fd(hostname, port);

    if(socket_fd != 3)
        cout << "ERROR CONECTION" << endl;

    while (true) {
        string input;
        cout << "> ";
        cin >> input;

        if(input == "quit")
            break;

        try {
            int id = stoi(input);

            send(socket_fd, input.c_str(), input.size(), 0);
            char buf[100];
            memset(buf, '\0', 100);
            recv(socket_fd, buf, 100, 0);
            cout << "result: " << string(buf) << endl;

        } catch(...) {
            cout << "bad input" << endl;
        }


    }
}
