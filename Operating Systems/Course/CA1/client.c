#include "structs.h"
#include "network.h"
#include "utility.h"

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <stdlib.h>

// GET_CHUNK_COUNT
char* generate_getchunkcount_command() {
    char* header = (char*)malloc(MAX_DATA_SIZE * sizeof(char));
    char* end_char = header;

    strcpy(end_char, HEADER_GET_CHUNK_COUNT);
    end_char += strlen(HEADER_GET_CHUNK_COUNT);

    return header;
}

// GET_CHUNK|<part_num>
char* generate_getchunk_command(int part_num) {
    char* header = (char*)malloc(MAX_DATA_SIZE * sizeof(char));
    char* end_char = header;

    strcpy(end_char, HEADER_GET_CHUNK);
    end_char += strlen(HEADER_GET_CHUNK);

    strcpy(end_char, HEADER_SEPERATOR);
    end_char += strlen(HEADER_SEPERATOR);

    sprintf(end_char, "%d", part_num);

    return header;
}

int get_chunk_count(int sock_fd) {
    char* get_info_command = generate_getchunkcount_command();
    char* chunk_count = request(sock_fd, get_info_command);
    return atoi(chunk_count);
}

char* get_chunk(int sock_fd, int part_num) {
    char* getchunk_command = generate_getchunk_command(part_num);
    char* data = request(sock_fd, getchunk_command);
    data += strlen(DATA_MARKER) + strlen(HEADER_SEPERATOR);

    char* chunk = (char*)malloc(CHUNK_SIZE * sizeof(char));
    memcpy(chunk, data, CHUNK_SIZE);

    return chunk;
}

int download_and_save(char* hostname, char* port, int file_fd) {
    int sock_fd = create_socket_fd(hostname, port);
    int chunk_count = get_chunk_count(sock_fd);

    for (int i = 0; i < chunk_count; i++) {
        char* chunk = get_chunk(sock_fd, i);

        print("\nWRITE: ");
        write(0, chunk, CHUNK_SIZE);
        print("\n");

        write(file_fd, chunk, CHUNK_SIZE);
    }

    close(sock_fd);
    return 0;
}

int main(int argc, char *argv[])
{
    // Initial
    if (argc != 5) {
        fprintf(stderr, "usage: ./client hostname port name output_path\n");
        exit(1);
    }
    char* hostname = argv[1];
    char* port = argv[2];
    char* name = argv[3];
    char* output_path = argv[4];

    // Pre-processes file
    int file_fd = open(output_path, O_CREAT | O_APPEND | O_WRONLY);
    if (file_fd == -1) {
        perror("Can't create output file!");
        exit(1);
    }

    download_and_save(hostname, port, file_fd);

    close(file_fd);

    return 0;
}
