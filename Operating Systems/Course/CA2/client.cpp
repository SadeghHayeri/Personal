/*
** client.c -- a stream socket client demo
*/

#include <iostream>
#include <unistd.h>
#include "network.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr,"usage: client hostname port id\n");
        exit(1);
    }
    char* hostname = argv[1];
    char* port = argv[2];
    char* id = argv[3];

    int socket_fd = create_socket_fd(hostname, port);

    cout << "connect: " << socket_fd << endl;

    send(socket_fd, id, strlen(id), 0);
    char buf[100];
    recv(socket_fd, buf, 100, 0);
    cout << "result: " << string(buf) << endl;
}
