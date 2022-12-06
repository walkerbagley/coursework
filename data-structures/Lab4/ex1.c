/* Title: ex1.c
 * Abstract: TBD
 * Author: Walker Bagley
 * Email: wbagley@nd.edu
 * Estimate: TBD
 * Date: 9/13/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct account{
    int dollars, cents;
    char name[10];
    struct account* next;
} account;

typedef struct accountList{
    struct account* head;
} accountList;

void displayAll(accountList* list);
void displayNth(accountList* list, int n);
void append(accountList* list, int n, char name[10], int d, int c);
void appendNthPosition(accountList* list, int n, char name[10], int d, int c);
void deleteRecord(accountList* list, int n);
void deleteNthNode(accountList* list, int n);

int main(void){
    accountList* list = (accountList *)malloc(sizeof(accountList));
    list->head = NULL;

    char fileName[20];
    printf("Enter filename: ");
    fscanf(stdin, "%s", fileName);
    FILE* f = fopen(fileName, "r");
    if (f == NULL){
        printf("File does not exist.\n");
        return 0;
    }

    long unsigned int n;
    fscanf(f, "%lu\n", &n);
    int i;
    for (i = 0; i < n; i++){
        char name[10];
        int d, c;
        fscanf(f, "%s ", name);
        fscanf(f, "%d ", &d);
        fscanf(f, "%d\n", &c);
        append(list, 1, name, d, c);
    }

    fclose(f);

    printf("Records entered into a singly linked list.\nThis is a list of operations on the singly linked list.\n\t1. Display all nodes\n\t2. Display nth record\n\t3. Append a new record - Head or Tail? (H/T)\n\t4. Append a new record in the Nth position\n\t5. Delete a record - Head or Tail? (H/T)\n\t6. Delete Nth record\n");
    int run = 1;
    while (run){
        int choice;
        printf("\nEnter your choice: ");
        fscanf(stdin, "%d", &choice);
        switch (choice){
            case 1:
                displayAll(list);
                break;
            case 2:{
                int dispNum;
                printf("Enter n: ");
                fscanf(stdin, "%d", &dispNum);
                displayNth(list, dispNum);
                break;
            }
            case 3:{
                char ht;
                char insertName[10];
                double amt;
                printf("Append to head or tail? (H/T): ");
                fscanf(stdin, "\n%c", &ht);
                printf("Enter a name: ");
                fscanf(stdin, "%s", insertName);
                printf("Enter an amount: ");
                fscanf(stdin, "%lf", &amt);
                int headtail = (ht == 'h' || ht == 'H') ? 0 : 1;
                append(list, headtail, insertName, (int) amt, (int) ((amt - (int) amt) * 100 + 1));
                displayAll(list);
                break;
            }
            case 4:{
                int insertNum;
                char insertName[10];
                double amt;
                printf("Enter n: ");
                fscanf(stdin, "\n%d", &insertNum);
                printf("Enter a name: ");
                fscanf(stdin, "%s", insertName);
                printf("Enter an amount: ");
                fscanf(stdin, "%lf", &amt);
                appendNthPosition(list, insertNum, insertName, (int) amt, (int) ((amt - (int) amt) * 100 + 1));
                displayAll(list);
                break;
            }
            case 5:{
                char ht;
                printf("Delete from head or tail? (H/T): ");
                fscanf(stdin, "\n%c", &ht);
                int headtail = (ht == 'h' || ht == 'H') ? 0 : 1;
                deleteRecord(list, headtail);
                displayAll(list);
                break;
            }
            case 6:{
                int deleteNum;
                printf("Enter n: ");
                fscanf(stdin, "%d", &deleteNum);
                deleteNthNode(list, deleteNum);
                displayAll(list);
                break;
            }
            default:
                break;
        }
    }
    account* current = (account *)malloc(sizeof(account));
    current = list->head;
    while (current != NULL){
        account* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
    free(current);

    return 0;
}

void displayAll(accountList* list){
    account* current = (account *)malloc(sizeof(account));
    current = list->head;
    printf("\nDisplaying all records:\n");
    while (current != NULL){
        printf("\t%s %d %d\n", current->name, current->dollars, current->cents);
        current = current->next;
    }
    current = NULL;
    free(current);
}

void displayNth(accountList* list, int n){
    account* current = (account *)malloc(sizeof(account));
    current = list->head;
    printf("\nDisplaying record %d:\n", n);
    int i;
    for (i = 0; i < n - 1; i++) current = current->next;
    printf("\t%s %d %d\n", current->name, current->dollars, current->cents);
    current = NULL;
    free(current);
}

void append(accountList* list, int n, char name[10], int d, int c){
    account* insert = (account *)malloc(sizeof(account));
    strcpy(insert->name, name);
    insert->dollars = d;
    insert->cents = c;
    switch (n){
        case 0:
            insert->next = list->head;
            list->head = insert;
            break;
        case 1:
            insert->next = NULL;
            if (list->head == NULL){
                list->head = insert;
            }
            else {
                account* current = (account *)malloc(sizeof(account));
                current = list->head;
                while (current->next != NULL) current = current->next;
                current->next = insert;
            }
            break;
        default:
            break;
    }
    insert = NULL;
    free(insert);
}

void appendNthPosition(accountList* list, int n, char name[10], int d, int c){
    account* insert = (account *)malloc(sizeof(account));
    strcpy(insert->name, name);
    insert->dollars = d;
    insert->cents = c;
    int i;
    account* current = (account *)malloc(sizeof(account));
    current = list->head;
    for (i = 0; i < n - 2; i++) current = current->next;
    insert->next = current->next;
    current->next = insert;
    current = NULL;
    insert = NULL;
    free(current);
    free(insert);
}

void deleteRecord(accountList* list, int n){
    account* temp = (account *)malloc(sizeof(account));
    switch (n){
        case 0:{
            temp = list->head;
            list->head = temp->next;
            break;
        }
        case 1:{
            account* current = (account *)malloc(sizeof(account));
            current = list->head;
            while (current->next->next != NULL) current = current->next;
            temp = current->next;
            current->next = NULL;
            current = NULL;
            free(current);
            break;
        }
        default:
            break;
    }
    free(temp);
}

void deleteNthNode(accountList* list, int n){
    int i;
    account* current = (account *)malloc(sizeof(account));
    current = list->head;
    account* temp = current;
    if (n == 1){
        list->head = current->next;
    }
    else {
        for (i = 0; i < n - 2; i++) current = current->next;
        temp = current->next;
        current->next = temp->next;
    }
    free(temp);
    current = NULL;
    free(current);
}