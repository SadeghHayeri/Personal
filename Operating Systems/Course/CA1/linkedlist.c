#include "linkedlist.h"
#include <stdio.h>

void add_node(Node** head_pointer, int file_index, char* ip, char* port) {

	Node* new_node = (Node*)malloc(sizeof(Node));

	new_node->file_index = file_index;
	strcpy(new_node->ip, ip);
	strcpy(new_node->port, port);

	if ((*head_pointer) == NULL) {
		(*head_pointer) = new_node;
		new_node->next = NULL;
	} else {

		Node* curr_node = *head_pointer;
		while (curr_node->next != NULL)
			curr_node = curr_node->next;

		curr_node->next = new_node;
		new_node->next = NULL;

	}

}

Node* get_node(Node* head, int file_index) {

	if (head == NULL)
		return NULL;

	Node* curr_node = head;
	while (curr_node->file_index != file_index) {
		if (curr_node->next == NULL)
			return NULL;
		curr_node = curr_node->next;
	}

	return curr_node;

}

int get_nodes_count(Node* head) {
	int count = 0;

	Node* curr_node = head;
	while (curr_node != NULL) {
		count++;
		curr_node = curr_node->next;
	}

	return count;
}

void print_list(Node* head) {
	printf("-> ");
	while (head != NULL) {
		printf("%s -> ", head->ip);
		head = head->next;
	}
	printf("\n");
}
// int delete_node(Node* head, char* ip)
