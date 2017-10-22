/*
** client.c -- a stream socket client demo
*/

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

/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>

#include <arpa/inet.h>

#include "structs.h"

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int create_socket_fd(char* ip, char* port) {
    int sock_fd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo(ip, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sock_fd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sock_fd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sock_fd);
            perror("client: connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    return sock_fd;
}

// ADD_FILE|<name>|<part_num>
char* get_initial_command(char* name, char* part) {
    char* header = (char*)malloc(MAX_DATA_SIZE * sizeof(char));
    char* end_char = header;

    strcpy(end_char, HEADER_ADD_FILE);
    end_char += strlen(HEADER_ADD_FILE);

    strcpy(end_char, HEADER_SEPERATOR);
    end_char += strlen(HEADER_SEPERATOR);

    strcpy(end_char, name);
    end_char += strlen(name);

    strcpy(end_char, HEADER_SEPERATOR);
    end_char += strlen(HEADER_SEPERATOR);

    strcpy(end_char, part);
    end_char += strlen(part);

    return header;
}

char* request(int sock_fd, char* msg) {
    char* response = (char*)malloc(MAX_DATA_SIZE * sizeof(char));
    send(sock_fd, msg, strlen(msg), 0);
    recv(sock_fd, response, MAX_DATA_SIZE, 0);
    return response;
}

int main(int argc, char *argv[])
{

    if (argc != 6) {
        fprintf(stderr,"usage: client hostname port file_path name part_num\n");
        exit(1);
    }
    char* hostname = argv[1];
    char* port = argv[2];
    char* file_path = argv[3];
    char* name = argv[4];
    char* part_num = argv[5];

    int file_fd = open(file_path, O_RDONLY);
    if (file_fd == -1) {

        perror("File Not Found!");
        exit(1);
    }

    int sock_fd = create_socket_fd(hostname, port);

    char* header = get_initial_command(name, part_num);
    char* response = request(sock_fd, header);
    write(0, response, strlen(response));

    close(sock_fd);
    return 0;
}
