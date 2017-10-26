#include "structs.h"
#include "network.h"
#include "utility.h"

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <stdlib.h>

#include <sys/stat.h>

int FILE_FD;

// ADD_FILE|<name>|<part_num>|<listener_port>
char* generate_initial_command(char* name, char* part_num, char* listener_port) {
    char* header = (char*)malloc(MAX_DATA_SIZE * sizeof(char));
    memset(header, '\0', MAX_DATA_SIZE);
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

    char* header = generate_initial_command(name, part_num, listener_port);
    char* response = request(sock_fd, header);
    // close(sock_fd);

    int is_save = (strcmp(response, OK_MESSAGE) == 0);
    return is_save;
}

char* handle_get_chunk_count(char* ip, char** data) {
    struct stat buf;
    fstat(FILE_FD, &buf);
    int file_size = buf.st_size;

    int chunk_count = (file_size / CHUNK_SIZE) + (file_size % CHUNK_SIZE != 0 ? 1 : 0);

    char* response = (char*)malloc(MAX_DATA_SIZE * sizeof(char));
    memset(response, '\0', MAX_DATA_SIZE);
    sprintf(response, "%d", chunk_count);
    return response;
}

char* handle_get_chunk(char* ip, char** data) {
    int part_num = atoi(data[1]);
    char* chunk = (char*)malloc((CHUNK_SIZE + strlen(DATA_MARKER) + 1) * sizeof(char));
    memset(chunk, '\0', (CHUNK_SIZE + strlen(DATA_MARKER) + 1));

    char* end_char = chunk;
    strcpy(end_char, DATA_MARKER);
    end_char += strlen(DATA_MARKER);

    strcpy(end_char, HEADER_SEPERATOR);
    end_char += strlen(HEADER_SEPERATOR);

    lseek(FILE_FD, part_num * CHUNK_SIZE, 0);
    read(FILE_FD, end_char, CHUNK_SIZE);

    return chunk;
}

char* request_handler(int id, char* ip, char* req) {

    char** data = split(req, HEADER_SEPERATOR); //TODO: free
    char* command = data[0];

    int is_get_chunk_count = (strcmp(command, HEADER_GET_CHUNK_COUNT) == 0);
    if (is_get_chunk_count) {
        return handle_get_chunk_count(ip, data);
    }

    int is_get_chunk = (strcmp(command, HEADER_GET_CHUNK) == 0);
    if (is_get_chunk) {
        return handle_get_chunk(ip, data);
    }

    return BAD_COMMAND;
}

void disconnect_handler(int id) {

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
    FILE_FD = open(file_path, O_RDONLY);
    if (FILE_FD == -1) {
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

    listen_to_clients(listener, listener_port, request_handler, disconnect_handler);

    return 0;
}
