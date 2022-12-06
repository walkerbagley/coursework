/* Title: ex3.c
 * Abstract: TBD
 * Author: Walker Bagley
 * Email: wbagley@nd.edu
 * Estimate: 1.5 hr
 * Date: 9/6/2022
 */

#include <stdio.h>
#include <stdlib.h>

void printArray(int* a, int s);
int arrayContains(int* a, int s, int n);
void reverseArray(int* a, int s);

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
    fprintf(stdout, "Operations:\n\t1. Append a number\n\t2. Delete an element\n\t3. Reverse the array\n");

    n = 1;
    int choice;
    char cont;
    while (n){
        fprintf(stdout, "\nEnter your option: ");
        fscanf(stdin, "%d", &choice);
        if (choice == 1){
            s++;
            arr = realloc(arr, s * sizeof(int));
            fprintf(stdout, "Enter a number to append: ");
            arr[s-1] = 0;
            while (arr[s-1] < 1 || arrayContains(arr, s - 1, arr[s-1])){
                fscanf(stdin, "\n%d", &arr[s-1]);
                if (arr[s-1] < 1) fprintf(stdout, "Please enter a positive number: ");
                else if (arrayContains(arr, s - 1, arr[s-1])){
                    fprintf(stdout, "%d is already in the array.\n", arr[s-1]);
                    printArray(arr, s - 1);
                    fprintf(stdout, "Please enter a positive number: ");
                }
            }
        }
        else if (choice == 2){
            s--;
            int i;
            int d = -1;
            fprintf(stdout, "Enter a number to delete: ");
            while (!arrayContains(arr, s + 1, d)){
                fscanf(stdin, "\n%d", &d);
                if (!arrayContains(arr, s + 1, d)){
                    fprintf(stdout, "%d is not in the array.\n", d);
                    printArray(arr, s + 1);
                    fprintf(stdout, "Please enter a number in the array: ");
                }
            }
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
        else if (choice == 3){
            reverseArray(arr, s);
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

int arrayContains(int* a, int s, int n){
    int i;
    int v = 0;
    for (i = 0; i < s; i++){
        if (a[i] == n) v = 1;
    }
    return v;
}

void reverseArray(int* a, int s){
    int temp[s];
    int i;
    for (i = s; i > 0; i--) temp[s - i] = a[i - 1];
    for (i = 0; i < s; i++) a[i] = temp[i];
}