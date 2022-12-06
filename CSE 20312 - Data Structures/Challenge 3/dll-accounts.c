/* Title: dll-accounts.c
 * Abstract: This program expands on the lab exercise from last week with an account structure as the node in a doubly linked list. There are then 15 functions to choose from that operate on said list of accounts, doing everything from showing duplicates, inserting new accounts, updating account balances, deleting accounts, searching accounts, and more.
 * Author: Walker Bagley
 * Email: wbagley@nd.edu
 * Estimate: 8 hours
 * Date: 9/18/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// account node struct
typedef struct account{
    int dollars, cents;
    char name[10];
    struct account* prev;
    struct account* next;
} account;

// list struct
typedef struct accountList{
    struct account* head;
    struct account* tail;
} accountList;

// function headers
void displayAll(accountList* list);
void displayNth(accountList* list, int n);
void append(accountList* list, int n, char name[10], int d, int c);
void appendNthPosition(accountList* list, int n, char name[10], int d, int c);
void deleteRecord(accountList* list, int n);
void deleteNthNode(accountList* list, int n);
void find(accountList* list, char* name);
void addMoney(accountList* list, char* name, int d, int c);
void average(accountList* list);
void displayAmountGreaterThan(accountList* list, double v);
void findMax(accountList* list);
void findMin(accountList* list);
void hasDuplicates(accountList* list);
void getNumberOfRecords(accountList* list);
void displayEven(accountList* list);
void displayOdd(accountList* list);
void reverseList(accountList* list);
// void convertCircular(accountList* list);
void moveFirstToLast(accountList* list);
void moveNtoM(accountList* list, int n, int m);

int main(void){
    // allocate space for a list and set each endpoint to null
    accountList* list = (accountList *)malloc(sizeof(accountList));
    list->head = NULL;
    list->tail = NULL;

    // read in filename from user and open it
    char fileName[20];
    printf("Enter filename: ");
    fscanf(stdin, "%s", fileName);
    FILE* f = fopen(fileName, "r");
    if (f == NULL){
        printf("File does not exist.\n");
        return 0;
    }

    // read in data from the file, starting with number of entries
    long unsigned int n;
    fscanf(f, "%lu\n", &n);
    int i;
    for (i = 0; i < n; i++){
        char name[10];
        int d, c;
        fscanf(f, "%s %d %d\n", name, &d, &c);
        append(list, 1, name, d, c);
    }

    fclose(f);

    // print menu
    printf("Records entered into a doubly linked list.\nThis is a list of operations on the doubly linked list.\n\t 1. Display all nodes\n\t 2. Display nth record\n\t 3. Append a new record - Head or Tail? (H/T)\n\t 4. Append a new record in the Nth position\n\t 5. Delete a record - Head or Tail? (H/T)\n\t 6. Delete Nth record\n\t 7. Find a record\n\t 8. Add money to account\n\t 9. Average all amounts\n\t10. Display the records of people with more than n.m\n\t    (n=dollars, m=cents) in their account\n\t11. Find max amount\n\t12. Find min amount\n\t13. Check for duplicates\n\t14. Get number of records\n\t15. Display even numbered records\n\t16. Display odd numbered records\n\t17. Reverse the list\n\t18. Convert into circular list\n\t19. Move the first record in the linked list to the end\n\t20. Move the nth record in the list to mth position");

    // enter program loop
    int run = 1;
    while (run){
        // get user input for choice of operations
        int choice;
        printf("\nEnter your choice: ");
        fscanf(stdin, "%d", &choice);
        fflush(stdin);
        switch (choice){
            // displays all account info
            case 1:{
                displayAll(list);
                break;
            }
            // displays the account in the nth position
            case 2:{
                int dispNum;
                printf("Enter n: ");
                fscanf(stdin, "%d", &dispNum);
                displayNth(list, dispNum);
                break;
            }
            // appends an account to the head or tail of the list
            case 3:{
                char ht;
                char insertName[10];
                double amt, d, c;
                printf("Append to head or tail? (H/T): ");
                fscanf(stdin, "\n%c", &ht);
                printf("Enter a name: ");
                fscanf(stdin, "%s", insertName);
                printf("Enter an amount: ");
                fscanf(stdin, "%lf", &amt);
                c = modf(amt, &d);
                int headtail = (ht == 'h' || ht == 'H') ? 0 : 1;
                append(list, headtail, insertName, (int) d, (int) (c * 100));
                displayAll(list);
                break;
            }
            // appends an account in the nth position
            case 4:{
                int insertNum;
                char insertName[10];
                double amt, d, c;
                printf("Enter n: ");
                fscanf(stdin, "\n%d", &insertNum);
                printf("Enter a name: ");
                fscanf(stdin, "%s", insertName);
                printf("Enter an amount: ");
                fscanf(stdin, "%lf", &amt);
                c = modf(amt, &d);
                appendNthPosition(list, insertNum, insertName, (int) d, (int) (c * 100));
                break;
            }
            // deletes an account from the head or tail of the list
            case 5:{
                char ht;
                printf("Delete from head or tail? (H/T): ");
                fscanf(stdin, "\n%c", &ht);
                int headtail = (ht == 'h' || ht == 'H') ? 0 : 1;
                deleteRecord(list, headtail);
                break;
            }
            // deletes an account from the nth position
            case 6:{
                int deleteNum;
                printf("Enter n: ");
                fscanf(stdin, "%d", &deleteNum);
                deleteNthNode(list, deleteNum);
                break;
            }
            // searches for and displays accounts with a user inputted name
            case 7:{
                char searchName[10];
                printf("Enter a name: ");
                fscanf(stdin, "%s", searchName);
                find(list, searchName);
                break;
            }
            // adds a user specified amount to a user specified account
            case 8:{
                char searchName[10];
                double amt, d, c;
                printf("Enter a name: ");
                fscanf(stdin, "%s", searchName);
                printf("Enter an amount: ");
                fscanf(stdin, "%lf", &amt);
                c = modf(amt, &d);
                addMoney(list, searchName, (int) d, (int) (c * 100));
                break;
            }
            // prints the average balance of all accounts in the list
            case 9:{
                average(list);
                break;
            }
            // displays all accounts with a balance more than a user specified amount
            case 10:{
                double amt;
                printf("Enter an amount: ");
                fscanf(stdin, "%lf", &amt);
                displayAmountGreaterThan(list, amt);
                break;
            }
            // displays account with the greatest balance
            case 11:{
                findMax(list);
                break;
            }
            // displays account with the smallest balance
            case 12:{
                findMin(list);
                break;
            }
            // displays all accounts that share a name with another account
            case 13:{
                hasDuplicates(list);
                break;
            }
            // prints the number of accounts in the list
            case 14:{
                getNumberOfRecords(list);
                break;
            }
            // displays the even numbered accounts (2nd, 4th, 6th...)
            case 15:{
                displayEven(list);
                break;
            }
            // displays the odd numbered accounts (1st, 3rd, 5th...)
            case 16:{
                displayOdd(list);
                break;
            }
            // reverses the order of the doubly linked list and then prints the new one
            case 17:{
                reverseList(list);
                break;
            }
            // connects the head and tail of the list
            // case 18:{
            //     convertCircular(list);
            //     break;
            // }
            // moves the first node in the list to the last position
            case 19:{
                moveFirstToLast(list);
                break;
            }
            // moves the nth node to the mth position in the list
            case 20:{
                int Num1, Num2;
                printf("Enter n: ");
                fscanf(stdin, "%d", &Num1);
                printf("Enter m: ");
                fscanf(stdin, "%d", &Num2);
                moveNtoM(list, Num1, Num2);
                break;
            }
            default:
                break;
        }
        // checks user input to continue or quit
        char r;
        printf("Continue? (Y/N): ");
        fscanf(stdin, "\n");
        fscanf(stdin, "%c", &r);
        run = (r == 'Y' || r == 'y') ? 1 : 0;
    }

    // frees memory from every node in the list and then the list itself
    account* current = list->head;
    account* temp;
    while (current != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }
    free(current);
    free(list);

    return 0;
}

// iterates through the list, printing the info for each account
void displayAll(accountList* list){
    account* current = list->head;
    printf("\nDisplaying all records:\n");
    while (current != NULL){
        printf("\t%s %d %d\n", current->name, current->dollars, current->cents);
        current = current->next;
    }
}

// iterates to the nth element and prints that account's info
void displayNth(accountList* list, int n){
    account* current = list->head;
    printf("\nDisplaying record %d:\n", n);
    int i;
    for (i = 0; i < n - 1; i++) current = current->next;
    printf("\t%s %d %d\n", current->name, current->dollars, current->cents);
}

// appends to the head or tail of the list with the info passed into the function
void append(accountList* list, int n, char name[10], int d, int c){
    account* insert = (account *)malloc(sizeof(account));
    strcpy(insert->name, name);
    insert->dollars = d;
    insert->cents = c;
    insert->prev = NULL;
    insert->next = NULL;
    // if list is empty, set it up here
    if (list->head == NULL){
        list->head = insert;
        list->tail = insert;
    }
    // append to head
    else if (n == 0){
        insert->next = list->head;
        insert->next->prev = insert;
        list->head = insert;
    }
    // append to tail
    else if (n == 1){
        insert->prev = list->tail;
        insert->prev->next = insert;
        list->tail = insert;
    }
}

// appends to the nth position in the list with the info passed into the function
void appendNthPosition(accountList* list, int n, char name[10], int d, int c){
    account* insert = (account *)malloc(sizeof(account));
    strcpy(insert->name, name);
    insert->dollars = d;
    insert->cents = c;
    insert->prev = NULL;
    insert->next = NULL;
    // iterate until the n-1 element is reached and then append the insert node
    int i;
    account* current = list->head;
    for (i = 0; i < n - 2; i++) current = current->next;
    insert->next = current->next;
    insert->prev = current;
    insert->next->prev = insert;
    current->next = insert;
    displayAll(list);
}

// deletes a record from the head or tail of the list
void deleteRecord(accountList* list, int n){
    account* temp;
    switch (n){
        // delete from head
        case 0:{
            temp = list->head;
            list->head = temp->next;
            break;
        }
        // delete from tail
        case 1:{
            account* current = list->head;
            while (current->next->next != NULL) current = current->next;
            temp = current->next;
            current->next = NULL;
            break;
        }
        default:
            break;
    }
    free(temp);
    displayAll(list);
}

// deletes the nth node of the list
void deleteNthNode(accountList* list, int n){
    int i;
    account* current = list->head;
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
    displayAll(list);
}

// searches for the account with a user specified name
void find(accountList* list, char* name){
    account* current = list->head;
    printf("\nShowing records with name %s:\n", name);
    while (current != NULL){
        if (!strcmp(current->name, name)) printf("\t%s %d %d\n", current->name, current->dollars, current->cents);
        current = current->next;
    }
}

// finds an account with the given name and then adds a user specified amount to that account
void addMoney(accountList* list, char* name, int d, int c){
    account* current = list->head;
    while (current != NULL){
        if (!strcmp(current->name, name)){
            int cents = current->cents + c;
            current->dollars += d + (cents / 100);
            current->cents = cents % 100;
            break;
        }
        current = current->next;
    }
    displayAll(list);
}

// averages the amount of money in all the accounts contained by the list
void average(accountList* list){
    account* current = list->head;
    double s = 0;
    int n = 0;
    while (current != NULL){
        s += (double) current->dollars;
        s += (double) current->cents / 100;
        n++;
        current = current->next;
    }
    printf("Account average: $%.2lf\n", s / n);
}

// displays accounts with balances greater than the given user specified threshold
void displayAmountGreaterThan(accountList* list, double v){
    account* current = list->head;
    double amt;
    printf("Displaying records with amount > %.2lf:\n", v);
    while (current != NULL){
        amt = current->dollars + ((double) current->cents / 100);
        if (amt >= v) printf("\t%s %d %d\n", current->name, current->dollars, current->cents);
        current = current->next;
    }
}

// finds the account with the largest balance and displays it
void findMax(accountList* list){
    account* max = list->head;
    account* current = max->next;
    while (current != NULL){
        if (current->dollars > max->dollars || (current->dollars == max->dollars && current->cents > max->cents)) max = current;
        current = current->next;
    }
    printf("Displaying record with max amount:\n\t%s %d %d\n", max->name, max->dollars, max->cents);
}

// finds the account with the smallest balance and displays it
void findMin(accountList* list){
    account* min = list->head;
    account* current = min->next;
    while (current != NULL){
        if (current->dollars < min->dollars || (current->dollars == min->dollars && current->cents < min->cents)) min = current;
        current = current->next;
    }
    printf("Displaying record with min amount:\n\t%s %d %d\n", min->name, min->dollars, min->cents);
}

// iterates through the list and prints out any duplicate accounts and their information
void hasDuplicates(accountList* list){
    account* temp = list->head;
    account* current;
    printf("Displaying duplicate records:\n");
    while (temp != NULL){
        current = temp->next;
        while (current != NULL){
            if (!strcmp(temp->name, current->name)) printf("\t%s %d %d\n\t%s %d %d\n", temp->name, temp->dollars, temp->cents, current->name, current->dollars, current->cents);
            current = current->next;
        }
        temp = temp->next;
    }
}

// tallies and prints the number of accounts contained in the list
void getNumberOfRecords(accountList* list){
    account* current = list->head;
    int n = 0;
    while (current != NULL){
        n++;
        current = current->next;
    }
    printf("Number of records: %d\n", n);
}

// displays every other account that is an even number (2nd, 4th, 6th, etc)
void displayEven(accountList* list){
    account* current = list->head;
    printf("Displaying even records:\n");
    while (current != NULL){
        if (current->next != NULL) current = current->next;
        else break;
        printf("\t%s %d %d\n", current->name, current->dollars, current->cents);
        current = current->next;
    }
}

// displays every other account that is an odd number (1st, 3rd, 5th, etc)
void displayOdd(accountList* list){
    account* current = list->head;
    printf("Displaying odd records:\n");
    while (current != NULL){
        printf("\t%s %d %d\n", current->name, current->dollars, current->cents);
        current = current->next->next;
    }
}

// reverses the list of nodes and prints the new reversed list for confirmation
void reverseList(accountList* list){
    list->head = list->tail;
    account* current = list->tail;
    while (current != NULL){
        account* temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        if (current->prev == NULL) list->tail = current;
        current = current->next;
    }
    displayAll(list);
}

// I wrote this function as I thought it should be written and it works as intended when called, however, connecting the endpoints of the list messes with the rest of my code knowing when to end its iterations of the list so I am leaving it commented out so the rest of my program works perfectly fine.
// void convertCircular(accountList* list){
//     list->head->prev = list->tail;
//     list->tail->next = list->head;
//     printf("Address of head: %p\n", list->head);
//     printf("Address of tail: %p\n", list->tail);
//     printf("Address of head->prev: %p\n", list->head->prev);
//     printf("Address of tail->next: %p\n", list->tail->next);
// }

// moves first account in the list to the end, setting each prev, next attribute accordingly
void moveFirstToLast(accountList* list){
    list->tail->next = list->head;
    list->head->prev = list->tail;
    list->head = list->head->next;
    list->tail = list->tail->next;
    list->head->prev = NULL;
    list->tail->next = NULL;
    displayAll(list);
}

// move the node in the nth position to the mth position under two cases
void moveNtoM(accountList* list, int n, int m){
    account* accn = NULL;
    account* accm = NULL;
    account* current = list->head;
    int i;
    // case 1: n < m, so n has to be moved to AFTER m in order to be in the mth position
    if (m > n){
        for (i = 1; i <= n; i++){
            if (i == n) accn = current;
            current = current->next;
        }
        for (i = n + 1; i <= m; i++){
            if (i == m) accm = current;
            current = current->next;
        }
        accn->prev->next = accn->next;
        accn->next->prev = accn->prev;
        accn->prev = accm;
        accn->next = accm->next;
        accm->next->prev = accn;
        accm->next = accn;
    }
    // case 1: m < n, so n has to be moved to BEFORE m in order to be in the mth position
    else if (n > m){
        for (i = 1; i <= m; i++){
            if (i == m) accm = current;
            current = current->next;
        }
        for (i = m + 1; i <= n; i++){
            if (i == n) accn = current;
            current = current->next;
        }
        accn->prev->next = accn->next;
        accn->next->prev = accn->prev;
        accn->prev = accm->prev;
        accm->prev->next = accn;
        accn->next = accm;
        accm->prev = accn;
    }
    displayAll(list);
}