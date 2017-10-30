#include "structs.h"
#include "network.h"
#include "utility.h"
#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <stdlib.h>

// GET_CHUNK_COUNT
void generate_getchunkcount_command(Max_size_data result) {
    strcat(result, HEADER_GET_CHUNK_COUNT);
}

// GET_CHUNK|<part_num>
void generate_getchunk_command(Max_size_data result, int part_num) {
    char part_num_string[MAX_DATA_SIZE];
    num_to_string(part_num, part_num_string);

    strcat(result, HEADER_GET_CHUNK);
    strcat(result, HEADER_SEPARATOR);
    strcat(result, part_num_string);
}

void generate_getcontributers_command(Max_size_data result, char* name) {
    strcat(result, HEADER_GET_COUNTRIBUTERS);
    strcat(result, HEADER_SEPARATOR);
    strcat(result, name);
}

int get_chunk_count(int sock_fd) {
    char getinfo_command[MAX_DATA_SIZE];
    memset(getinfo_command, '\0', MAX_DATA_SIZE);
    generate_getchunkcount_command(getinfo_command);
    char chunk_count[MAX_DATA_SIZE];
    request(chunk_count, sock_fd, getinfo_command);
    return atoi(chunk_count);
}

void get_chunk_and_save(int sock_fd, int part_num, int file_fd) {
    char getchunk_command[MAX_DATA_SIZE];
    memset(getchunk_command, '\0', MAX_DATA_SIZE);
    generate_getchunk_command(getchunk_command, part_num);
    char data[MAX_DATA_SIZE];
    request(data, sock_fd, getchunk_command);

    char* end_char = data;
    end_char += strlen(DATA_MARKER) + strlen(HEADER_SEPARATOR);

    // get this_chunk_size
    char this_chunk_size[20];
    int max_num_length = num_len(CHUNK_SIZE);
    memcpy(this_chunk_size, end_char, max_num_length);
    int this_chunk_size_num = atoi(this_chunk_size);
    end_char += max_num_length;

    end_char += strlen(HEADER_SEPARATOR);

    write(file_fd, end_char, this_chunk_size_num);
}

int connect_download_append(char* hostname, char* port, int file_fd) {
    int sock_fd = create_socket_fd(hostname, port);
    int chunk_count = get_chunk_count(sock_fd);

    for (int i = 0; i < chunk_count; i++)
        get_chunk_and_save(sock_fd, i, file_fd);

    close(sock_fd);
    return 0;
}

void connect_download_append_all(Node* contributers_head, int file_fd) {
    Node* cursor = contributers_head;
    while(cursor != NULL)
    {
        connect_download_append(cursor->ip, cursor->port, file_fd);
        cursor = cursor->next;
    }
}

Node* get_contributers(int mainserver_sock_fd, char* name) {
    char getcontributers_command[MAX_DATA_SIZE];
    memset(getcontributers_command, '\0', MAX_DATA_SIZE);
    generate_getcontributers_command(getcontributers_command, name);
    char response[MAX_DATA_SIZE];
    request(response, mainserver_sock_fd, getcontributers_command);

    Split_data data;
    split(response, data, HEADER_SEPARATOR);
    int number_of_contributers = atoi(data[0]);

    printf("%s\n", data[3]);

    Node* contributers_head = NULL;
    for (int i = 0; i < number_of_contributers; ++i) {
        char contributer_data[MAX_DATA_SIZE][MAX_DATA_SIZE];
        split(data[1+i], contributer_data, HEADER_SUB_SEPARATOR);

        int file_index = atoi(contributer_data[0]);
        char* ip = contributer_data[1];
        char* port = contributer_data[2];

        contributers_head = prepend(contributers_head, file_index, -1, ip, port);
        // printf("%d - %s - %s\n",file_index, ip, port );
    }
    contributers_head = insertion_sort(contributers_head);

    return contributers_head;
}

int main(int argc, char *argv[]) {
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

    int mainserver_sock_fd = create_socket_fd(hostname, port);
    Node* contributers_head = get_contributers(mainserver_sock_fd, name);
    close(mainserver_sock_fd);

    connect_download_append_all(contributers_head, file_fd);

    close(file_fd);

    return 0;
}
