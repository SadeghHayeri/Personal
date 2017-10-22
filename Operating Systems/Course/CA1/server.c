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

int main(int argc, char *argv[])
{

    if (argc != 6) {
        fprintf(stderr,"usage: ./server hostname port file_path name part_num\n");
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
