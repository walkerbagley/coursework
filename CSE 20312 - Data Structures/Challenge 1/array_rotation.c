/* Title: array_rotation.c
 * Abstract: This program takes input from a text file for the number of items in an array, how many rotations to do, and the direction of rotation as well as the array of numbers itself. It then computes and outputs the result of said transformation.
 * Author: Walker Bagley
 * Email: wbagley@nd.edu
 * Estimate: 30 min
 * Date: 8/30/2022
 */
#include <stdio.h>
#include <stdlib.h>

void rightRotation(int* a, int s);
void leftRotation(int* a, int s);

int main(void){

    FILE* f = fopen("input.txt", "r");

    if (f == NULL) {
        printf("File does not exist!");
        return 0;
    }

    int l;
    fscanf(f, "%d ", &l);
    int* arr = malloc(l * sizeof(int));

    int r;
    fscanf(f, "%d ", &r);

    char d;
    fscanf(f, "%c\n", &d);

    int n = 0;
    while (!feof(f)){
        fscanf(f, "%d ", &arr[n]);
        n++;
    }

    fclose(f);

    int i;
    for (i = 0; i < r; i++){
        if (d == 'L') leftRotation(arr, l);
        else if (d == 'R') rightRotation(arr, l);
    }

    for (i = 0; i < l; i++){
        fprintf(stdout, "%d ", arr[i]);
    }

    fprintf(stdout, "\n");
    free(arr);
    
    return 0;
}

void rightRotation(int* a, int s){
    int i, temp;
    temp = a[s-1];
    for(i = s; i > 0; i--){
        a[i] = a[i-1];
    }
    a[0] = temp;
}

void leftRotation(int* a, int s){
    int i, temp;
    temp = a[0];
    for(i = 0; i < s; i++){
        a[i] = a[i+1];
    }
    a[s-1] = temp;
}