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

char* request_handler(char* ip, char* req) {
    return "BAD COMMMAND";
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


    // Open listener service port
    int listener = create_listener_fd(listener_port);


    // Send file info to mainServer
    int is_save = initial_to_mainserver(hostname, port, file_path, name, part_num, listener_port);
    if (is_save) {
        print("-> Initial to mainServer complete!\n");
    } else {
        perror("Err: initial_to_mainserver()");
        exit(1);
    }

    listen_to_clients(listener, listener_port, request_handler);

    return 0;
}
