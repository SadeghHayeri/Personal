#include "structs.h"
#include "network.h"
#include "utility.h"

#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <stdlib.h>

int FILE_FD;

void handle_get_chunk_count(Max_size_data result, char* ip, Split_data data) {
    long file_size = get_file_size(FILE_FD);
    int chunk_count = (file_size / CHUNK_SIZE) + (file_size % CHUNK_SIZE != 0 ? 1 : 0);
    char chunk_count_string[MAX_DATA_SIZE];
    num_to_string(chunk_count, chunk_count_string);
    strcpy(result, chunk_count_string);
}

// DATA|<data-size>|<data>
void handle_get_chunk(Max_size_data result, char* ip, Split_data data) {
    int part_num = atoi(data[1]);
    char* end_char = result;

    strcpy(end_char, DATA_MARKER);
    end_char += strlen(DATA_MARKER);

    strcpy(end_char, HEADER_SEPARATOR);
    end_char += strlen(HEADER_SEPARATOR);

    long file_size = get_file_size(FILE_FD);
    long need_to_send = (file_size - (part_num * CHUNK_SIZE));
    int this_chunk_size = (need_to_send > CHUNK_SIZE) ? CHUNK_SIZE : need_to_send;

    int max_num_length = num_len(CHUNK_SIZE);
    int max_cur_length = num_len(this_chunk_size);

    // add ZEROS in start of size
    for (int i = 0; i < max_num_length - max_cur_length; ++i) {
        strcpy(end_char, "0");
        end_char++;
    }

    sprintf(end_char, "%d", this_chunk_size);
    end_char += num_len(this_chunk_size);

    strcpy(end_char, HEADER_SEPARATOR);
    end_char += strlen(HEADER_SEPARATOR);

    lseek(FILE_FD, part_num * CHUNK_SIZE, 0);
    read(FILE_FD, end_char, this_chunk_size);
}

void request_handler(Max_size_data response, int id, char* ip, char* req) {
    memset(response, '\0', MAX_DATA_SIZE);
    Split_data data;
    split(req, data, HEADER_SEPARATOR);
    char* command = data[0];

    int is_get_chunk_count = (strcmp(command, HEADER_GET_CHUNK_COUNT) == 0);
    if (is_get_chunk_count)
        return handle_get_chunk_count(response, ip, data);

    int is_get_chunk = (strcmp(command, HEADER_GET_CHUNK) == 0);
    if (is_get_chunk)
        return handle_get_chunk(response, ip, data);

    strcpy(response, BAD_COMMAND);
}

// ADD_FILE|<name>|<part_num>|<listener_port>
void generate_initial_command(Max_size_data result, char* name, char* part_num, char* listener_port) {
    strcat(result, HEADER_ADD_FILE);
    strcat(result, HEADER_SEPARATOR);
    strcat(result, name);
    strcat(result, HEADER_SEPARATOR);
    strcat(result, part_num);
    strcat(result, HEADER_SEPARATOR);
    strcat(result, listener_port);
}

int initial_to_mainserver(int main_server_fd, char* file_path, char* name, char* part_num, char* listener_port) {
    char header[MAX_DATA_SIZE];
    generate_initial_command(header, name, part_num, listener_port);
    char response[MAX_DATA_SIZE];
    request(response, main_server_fd, header);

    int is_save = (strcmp(response, OK_MESSAGE) == 0);
    return is_save;
}

void disconnect_handler(int id) {
    // do nothing!
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
    int main_server_fd = create_socket_fd(hostname, port);
    int is_save = initial_to_mainserver(main_server_fd, file_path, name, part_num, listener_port);
    if (is_save) {
        print("-> Initial to mainServer complete!\n");
    } else {
        perror("Err: initial_to_mainserver()");
        exit(1);
    }

    listen_to_clients(listener, listener_port, request_handler, disconnect_handler);

    close(main_server_fd);
    return 0;
}
