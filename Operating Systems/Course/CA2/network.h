#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <arpa/inet.h>

#include "structs.h"

#define MAX_DATA_SIZE 1000
typedef char Max_size_data[MAX_DATA_SIZE];

void *get_in_addr(struct sockaddr *sa);
int create_socket_fd(char* ip, char* port);
int create_listener_fd(char* port);
void request(Max_size_data response, int sock_fd, char* msg);
int accept_client(int listener, int port);

void sigchld_handler(int s);
void listen_to_clients(
    int listener,
    char* listener_port,
    void (*request_handler)(Max_size_data result, int id, char* ip, char* req),
    void (*disconnect_handler)(int id)
);



#endif
