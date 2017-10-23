#include "structs.h"
#include "utility.h"
#include "network.h"
#include "mainServerCore.h"

#include <unistd.h> // atoi

File* FILES;

char* handle_add_file(char* ip, char** data) {
    char* name = data[1];
    char* port = data[3];
    int part_num = atoi(data[2]);

    int status = add_file_piece(FILES, name, part_num, ip, port);
    if (status == 1)
        return "OK";
    else
        return "ERR";
}

char* request_handler(char* ip, char* req) {
    char** data = split(req, HEADER_SEPERATOR); //TODO: free
    char* command = data[0];

    int is_add_file = (strcmp(command, HEADER_ADD_FILE) == 0);
    if (is_add_file)
        return handle_add_file(ip, data);

    return "BAD COMMMAND";
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr,"usage: ./mainServer port\n");
        exit(1);
    }
    char* listener_port = argv[1];

    FILES = init_files_array();

    int listener = create_listener_fd(listener_port);
    listen_to_clients(listener, listener_port, request_handler);
    //
    // while(1) {  // main accept() loop
    //     int new_fd;
    //     char s[INET6_ADDRSTRLEN];
    //     struct sockaddr_storage their_addr; // connector's address information
    //     socklen_t sin_size = sizeof their_addr;
    //
    //     new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    //     if (new_fd == -1) {
    //         perror("accept");
    //         continue;
    //     }
    //
    //     inet_ntop(their_addr.ss_family,
    //         get_in_addr((struct sockaddr *)&their_addr),
    //         s, sizeof s);
    //     printf("server: got connection from %s\n", s);
    //
    //     if (!fork()) { // this is the child process
    //         close(sockfd); // child doesn't need the listener
    //
    //         char req[MAX_DATA_SIZE];
    //
    //         recv(new_fd, req, MAX_DATA_SIZE, 0);
    //         char* res = handle_request(FILES, s, req);
    //         send(new_fd, res, strlen(res), 0);
    //
    //         write(0, req, strlen(req));
    //         write(0, " -> ", 5);
    //         write(0, res, strlen(res));
    //
    //         close(new_fd);
    //         exit(0);
    //     }
    //     close(new_fd);  // parent doesn't need this
    // }

    return 0;
}
