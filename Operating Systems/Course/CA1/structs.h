#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_FILE_NAME 50
#define MAX_FILE_HANDLER 10
#define NOTSET "NOTSET"
#define IP_LEN 15   // worst case: 255.255.255.255

typedef struct node {
    int file_index;
    char ip[IP_LEN];
    int port;

    struct node *next;
} Node;

typedef struct file {
    char name[MAX_FILE_NAME];
    Node* contributers_head;
} File;

#endif
