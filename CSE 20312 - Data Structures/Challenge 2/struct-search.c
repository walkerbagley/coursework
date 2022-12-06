/* Title: struct-search.c
 * Abstract: This program reads in an array of bank customers and stores their information via a struct. The user is then able to search for the name of a customer and the program will output the relevant information.
 * Author: Walker Bagley
 * Email: wbagley@nd.edu
 * Estimate: 30 min
 * Date: 9/7/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct customer{
    char name[10];
    int acc;
    double balance;
} customer;

int main(void){
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
    customer c[30];
    int i;
    for (i = 0; i < n; i++){
        fscanf(f, "%s ", c[i].name);
        fscanf(f, "%d ", &c[i].acc);
        fscanf(f, "%lf\n", &c[i].balance);
    }

    fclose(f);

    int run = 1, m = 0;
    while (run){
        char search[10];
        m = 0;
        printf("\n------------------------------------------------\n  Record Finder - Enter a customer name: ");
        fscanf(stdin, "%s", search);
        printf("------------------------------------------------");
        for (i = 0; i < n; i++){
            if (strcmp(c[i].name, search) == 0){
                m++;
                printf("\n  Name: %s\n  Account: %d\n  Balance: %.2lf\n", c[i].name, c[i].acc, c[i].balance);
            }
        }
        if (m == 0) printf("\n  Fail. %s doesn't exist.\n", search);
        printf("------------------------------------------------\n\n  Continue? (y/n): ");
        char cont;
        fscanf(stdin, "\n");
        fscanf(stdin, "%c", &cont);
        if (cont == 'N' || cont == 'n'){
            run = 0;
            printf("\n  BYE!\n");
        }
    }

    return 0;
}