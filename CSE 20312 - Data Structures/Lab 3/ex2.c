/* Title: ex2.c
 * Abstract: TBD
 * Author: Walker Bagley
 * Email: wbagley@nd.edu
 * Estimate: 1.5 hr
 * Date: 9/6/2022
 */

#include <stdio.h>
#include <stdlib.h>

void printArray(int* a, int s);

int main(void){

    FILE* f = fopen("input.txt", "r");

    if (f == NULL) {
        printf("File does not exist!");
        return 0;
    }

    int s;
    fscanf(f, "%d\n", &s);
    int* arr = malloc(s * sizeof(int));

    int n = 0;
    while (!feof(f)){
        fscanf(f, "%d ", &arr[n]);
        n++;
    }

    fclose(f);

    printArray(arr, s);

    n = 1;
    int choice;
    char cont;
    while (n){
        fprintf(stdout, "Operations:\n\t1. Append a number\n\t2. Delete an element\n\nEnter your option: ");
        fscanf(stdin, "%d", &choice);
        if (choice == 1){
            s++;
            arr = realloc(arr, s * sizeof(int));
            fprintf(stdout, "Enter a number to append: ");
            fscanf(stdin, "\n%d", &arr[s-1]);
        }
        else if (choice == 2){
            s--;
            int d, i;
            fprintf(stdout, "Enter a number to delete: ");
            fscanf(stdin, "\n%d", &d);
            int temp[s];
            int n = 0;
            for (i = 0; i < s + 1; i++){
                if (arr[i] != d){
                    temp[n] = arr[i];
                    n++;
                }
            }
            arr = realloc(arr, s * sizeof(int));
            for (i = 0; i < s; i++) arr[i] = temp[i];
        }
        printArray(arr, s);
        fprintf(stdout, "Continue? (Y/N): ");
        fscanf(stdin, "\n%c", &cont);
        if (cont == 'n' || cont == 'N') n = 0;
    }

    fprintf(stdout, "\n");
    free(arr);
    
    return 0;
}

void printArray(int* a, int s){
    fprintf(stdout, "Array values: ");
    int i;
    for (i = 0; i < s; i++){
        fprintf(stdout, "%d ", a[i]);
    }
    fprintf(stdout, "\nArray size: %d\n", s);
}