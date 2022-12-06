/* Title: singly-linked-list.c
 * Author: Walker Bagley
 * Email: wbagley@nd.edu
 * Date: 9/7/2022
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct sll_node{
    int data;
    struct sll_node* next_node;
} sll_node;

typedef struct sllist{
    struct sll_node* head;
} sllist;

int main(void){
    sllist* list = (sllist *)malloc(sizeof(sllist));
    list->head = NULL;

    FILE* f = fopen("input.txt", "r");
    if (f == NULL){
        printf("File does not exist.\n");
        return 0;
    }

    free(list);

    return 0;
}

void insert(sllist* list, int v){
    sll_node* insert_node = (sll_node *)malloc(sizeof(sll_node));
    insert_node->data = v;
    insert_node->next_node = NULL;
    if (list->head == NULL){
        list->head = insert_node;
        return;
    }
    sll_node* current = list->head;
    while (current->next_node != NULL){
        current = current->next_node;
    }
    current->next_node = insert_node;
}

void destructor(sll_node* current){
    sll_node* temp;
    while(current != NULL){
        temp = current;
        current = current->next_node;
        free(temp);
    }
}

void print_list(sll_node* head_node){
    sll_node* current = head_node;
    while (current != NULL){
        printf("Current node address: %p\n", current);
        printf("Current node data: %p\n", current->data);
        current = current->next_node;
    }
}