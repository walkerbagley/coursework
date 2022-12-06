#include <stdio.h>
#include <stdlib.h>

typedef struct dll_node{
    int data;
    struct dll_node* prev;
    struct dll_node* next;
} dll_node;

typedef struct dllist{
    struct dll_node* head;
    struct dll_node* tail;
} dllist;

int main(void){

    dllist* list = (dllist *)malloc(sizeof(dllist));
    list->head = NULL;
    list->tail = NULL;

    FILE* f = fopen("input.txt", "r");
    if (f == NULL){
        printf("File does not exist.\n");
        return 0;
    }

    free(list);

    return 0;
}

void push_front(dllist* list, int v){
    dll_node* insert_node = (dll_node *)malloc(sizeof(dll_node));
    insert_node->data = v;
    insert_node->next = NULL;
    insert_node->prev = NULL;
    if (list->head == NULL){
        list->head = insert_node;
        list->tail = insert_node;
        return;
    }
    dll_node* ref = list->head;
    list->head = insert_node;
    list->head->next = ref;
    ref->prev = list->head;
}

void push_back(dllist* list, int v){
    dll_node* insert_node = (dll_node *)malloc(sizeof(dll_node));
    insert_node->data = v;
    insert_node->next = NULL;
    insert_node->prev = NULL;
    if (list->tail == NULL){
        list->head = insert_node;
        list->tail = insert_node;
        return;
    }
    dll_node* ref = list->tail;
    list->tail = insert_node;
    list->tail->prev = ref;
    ref->next = list->tail;
}