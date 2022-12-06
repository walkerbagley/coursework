/* Title: ex3.c
 * Abstract: FILL IN
 * Author: Walker Bagley
 * Email: wbagley@nd.edu
 * Estimate: 20 min
 * Date: 8/30/2022
 */
#include <stdio.h>
#include <stdlib.h>

void rightShift(int* a, int s);
void leftShift(int* a, int s);

int main(void){

    FILE* f = fopen("input.txt", "r");

    if (f == NULL) {
        printf("File does not exist!");
        return 0;
    }

    int* nums = malloc(100);

    int n = 0;
    while (!feof(f)){
        fscanf(f, "%d\n", &nums[n]);
        n++;
    }

    fclose(f);

    int i;
    fprintf(stdout, "Array values:");
    for (i = 0; i < n; i++){
        fprintf(stdout, " %d", nums[i]);
    }

    fprintf(stdout, "\nThis is a list of options:");
    fprintf(stdout, "\n\t1. Right Shift");
    fprintf(stdout, "\n\t2. Left Shift\n");

    int run = 1;
    while (run){
        fprintf(stdout, "\nEnter your option: ");
        int choice;
        fscanf(stdin, "%d", &choice);

        if (choice == 1) rightShift(nums, n);
        else if (choice == 2) leftShift(nums, n);

        fprintf(stdout, "New array values:");
        for (i = 0; i < n; i++){
            fprintf(stdout, " %d", nums[i]);
        }

        fprintf(stdout, "\nContinue? (Y/N): ");
        char cont;
        fscanf(stdin, "\n");
        fscanf(stdin, "%c", &cont);
        if (cont == 'N' || cont == 'n') run = 0;
    }

    fprintf(stdout, "\n");
    free(nums);
    
    return 0;
}

void rightShift(int* a, int s){
    int i;
    for(i = s; i > 0; i--){
        a[i] = a[i-1];
    }
    a[0] = 0;
}

void leftShift(int* a, int s){
    int i;
    for(i = 0; i < s; i++){
        a[i] = a[i+1];
    }
    a[s-1] = 0;
}