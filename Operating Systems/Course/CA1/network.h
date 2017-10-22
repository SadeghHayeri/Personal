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

#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <arpa/inet.h>

void *get_in_addr(struct sockaddr *sa);
int create_socket_fd(char* ip, char* port);
char* request(int sock_fd, char* msg);


#endif
