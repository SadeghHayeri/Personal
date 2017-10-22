#include "structs.h"
#include "utility.h"
#include "network.h"
#include "mainServerCore.h"

#include <unistd.h> // atoi

char* handle_request(File* files, char* req) {
    char** data = split(req, HEADER_SEPERATOR);

    char* command = data[0];

    int is_add_file = (strcmp(command, HEADER_ADD_FILE) == 0);
    if (is_add_file) {

        char* name = data[1];
        char* port = data[5];
        int part_num = atoi(data[2]);

        int status = add_file_piece(files, name, part_num, "172.0.0.1", "1000");
        if (status == 1)
            return "OK";
        else
            return "NO";

    }



    return "OK";
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr,"usage: ./mainServer port\n");
        exit(1);
    }
    char* port = argv[1];

    int sockfd = create_listener_fd(port);
    File* files = init_files_array();

    while(1) {  // main accept() loop
        int new_fd;
        char s[INET6_ADDRSTRLEN];
        struct sockaddr_storage their_addr; // connector's address information
        socklen_t sin_size = sizeof their_addr;

        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("server: got connection from %s\n", s);

        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener

            char req[MAX_DATA_SIZE];

            recv(new_fd, req, MAX_DATA_SIZE, 0);
            char* res = handle_request(files, req);
            send(new_fd, res, strlen(res), 0);

            write(0, req, strlen(req));
            write(0, " -> ", 5);
            write(0, res, strlen(res));

            close(new_fd);
            exit(0);
        }
        close(new_fd);  // parent doesn't need this
    }

    return 0;
}
