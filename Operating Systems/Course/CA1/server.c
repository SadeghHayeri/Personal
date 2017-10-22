#include "structs.h"
#include "network.h"

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

int initial_to_mainserver(char* hostname, char* port, char* file_path, char* name, char* part_num) {
    int sock_fd = create_socket_fd(hostname, port);

    char* header = get_initial_command(name, part_num);
    char* response = request(sock_fd, header);
    close(sock_fd);

    int is_save = (strcmp(response, OK_MESSAGE) == 0);
    return is_save;
}

int main(int argc, char *argv[])
{
    // initial
    if (argc != 6) {
        fprintf(stderr,"usage: ./server hostname port file_path name part_num\n");
        exit(1);
    }
    char* hostname = argv[1];
    char* port = argv[2];
    char* file_path = argv[3];
    char* name = argv[4];
    char* part_num = argv[5];

    // processes in file
    int file_fd = open(file_path, O_RDONLY);
    if (file_fd == -1) {
        perror("File Not Found!");
        exit(1);
    }

    // send file info to mainServer
    int is_save = initial_to_mainserver(hostname, port, file_path, name, part_num);
    if (is_save) {
        char* msg = "-> Initial to mainServer complete!";
        write(0, msg, strlen(msg));
    } else {
        perror("Err: initial_to_mainserver()");
        exit(1);
    }

    // listen to clients for file!

    return 0;
}
