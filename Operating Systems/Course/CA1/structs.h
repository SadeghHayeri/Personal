#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_FILE_NAME 50
#define MAX_FILE_HANDLER 10
#define NOTSET "NOTSET"
#define IP_LEN 22   // worst case: ::ffff:255.255.255.255
#define PORT_LEN 15   // worst case: 60000
#define MAX_RANDOM_PORT 60000
#define RANDOM_PORT_OFFSET 1000

#define MAX_DATA_SIZE 1000
#define MAX_SPLIT_BOX 20
#define CHUNK_SIZE 50
#define OK_MESSAGE "OK"
#define HEADER_ADD_FILE "ADD_FILE"
#define HEADER_GET_CHUNK_COUNT "GET_CHUNK_COUNT"
#define HEADER_GET_CHUNK "GET_CHUNK"
#define DATA_MARKER "DATA"
#define HEADER_SEPERATOR "<*>"
#define HEADER_SUB_SEPERATOR "<|>"


#define BACKLOG 10     // how many pending connections queue will hold

typedef struct node {
    int file_index;
    int id;
    char ip[IP_LEN];
    char port[PORT_LEN];

    struct node *next;
} Node;

typedef struct file {
    char name[MAX_FILE_NAME];
    Node* contributers_head;
} File;

#endif
