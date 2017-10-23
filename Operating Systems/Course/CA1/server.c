#include "structs.h"
#include "network.h"
#include "utility.h"

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <stdlib.h>

// ADD_FILE|<name>|<part_num>|<listener_port>
char* get_initial_command(char* name, char* part_num, char* listener_port) {
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

    strcpy(end_char, part_num);
    end_char += strlen(part_num);

    strcpy(end_char, HEADER_SEPERATOR);
    end_char += strlen(HEADER_SEPERATOR);

    strcpy(end_char, listener_port);
    end_char += strlen(listener_port);

    return header;
}

int initial_to_mainserver(char* hostname, char* port, char* file_path, char* name, char* part_num, char* listener_port) {
    int sock_fd = create_socket_fd(hostname, port);

    char* header = get_initial_command(name, part_num, listener_port);
    char* response = request(sock_fd, header);
    close(sock_fd);

    int is_save = (strcmp(response, OK_MESSAGE) == 0);
    return is_save;
}

int main(int argc, char *argv[])
{
    // Initial
    if (!(argc == 6 || argc == 7)) {
        fprintf(stderr,"usage: ./server hostname port file_path name part_num [listener_port]\n");
        exit(1);
    }
    char* hostname = argv[1];
    char* port = argv[2];
    char* file_path = argv[3];
    char* name = argv[4];
    char* part_num = argv[5];
    char listener_port[PORT_LEN];

    if (argc == 7)
        strcpy(listener_port, argv[6]);
    else {
        srand(time(NULL));
        int random_port = (rand() % MAX_RANDOM_PORT) + RANDOM_PORT_OFFSET;
        sprintf(listener_port, "%d", random_port);
    }

    // Pre-processes file
    int file_fd = open(file_path, O_RDONLY);
    if (file_fd == -1) {
        perror("File Not Found!");
        exit(1);
    }

    fd_set master;    // master file descriptor list
    fd_set read_fds;  // temp file descriptor list for select()
    int fdmax;        // maximum file descriptor number

    socklen_t addrlen;
    struct sockaddr_storage remoteaddr; // client address
    int newfd;        // newly accept()ed socket descriptor
    char remoteIP[INET6_ADDRSTRLEN];
    char buf[256];    // buffer for client data
    int nbytes;

    // clear the master and temp sets
    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    // Open listener service port
    int listener = create_listener_fd(listener_port);

    // add the listener to the master set
    FD_SET(listener, &master);

    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it's this one

    // Send file info to mainServer
    int is_save = initial_to_mainserver(hostname, port, file_path, name, part_num, listener_port);
    if (is_save) {
        print("-> Initial to mainServer complete!\n");
    } else {
        perror("Err: initial_to_mainserver()");
        exit(1);
    }

    // Listening to clients
    print("-> Listening to clients on port: ");
    print(listener_port);
    print("\n");
    // main loop
    for(;;) {
        read_fds = master; // copy it
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(4);
        }

        // run through the existing connections looking for data to read
        for(int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) { // we got one!!
                if (i == listener) {
                    // handle new connections
                    addrlen = sizeof remoteaddr;
                    newfd = accept(listener,
                        (struct sockaddr *)&remoteaddr,
                        &addrlen);

                    if (newfd == -1) {
                        perror("accept");
                    } else {
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax) {    // keep track of the max
                            fdmax = newfd;
                        }
                        printf("selectserver: new connection from %s on "
                            "socket %d\n",
                            inet_ntop(remoteaddr.ss_family,
                                get_in_addr((struct sockaddr*)&remoteaddr),
                                remoteIP, INET6_ADDRSTRLEN),
                            newfd);
                    }
                } else {
                    // handle data from a client
                    if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0) {
                        // got error or connection closed by client
                        if (nbytes == 0) {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                        } else {
                            perror("recv");
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    } else {
                        // we got some data from a client
                        for(int j = 0; j <= fdmax; j++) {
                            // send to everyone!
                            if (FD_ISSET(j, &master)) {
                                // except the listener and ourselves
                                if (j != listener && j != i) {
                                    if (send(j, buf, nbytes, 0) == -1) {
                                        perror("send");
                                    }
                                }
                            }
                        }
                    }
                } // END handle data from client
            } // END got new incoming connection
        } // END looping through file descriptors
    } // END for(;;)--and you thought it would never end!

    return 0;
}
