/* Title: array-merge.c
 * Abstract: This program reads in 2 arrays of integers in ascending order and then combines them dynamically, keeping the increasing order. Outputs for each step are printed to the console.
 * Author: Walker Bagley
 * Email: wbagley@nd.edu
 * Estimate: 45 min
 * Date: 9/11/2022
 */

#include <stdio.h>
#include <stdlib.h>

int main(void){
    
    char fileName[20];
    printf("Enter filename: ");
    fscanf(stdin, "%s", fileName);
    FILE* f = fopen(fileName, "r");
    if (f == NULL){
        printf("File does not exist.\n");
        return 0;
    }

    long unsigned int n, m;
    fscanf(f, "%lu\n", &n);
    int* arr1 = (int *)malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++) fscanf(f, "%d ", &arr1[i]);
    fscanf(f, "%lu\n", &m);
    int* arr2 = (int *)malloc(m * sizeof(int));
    for (i = 0; i < m; i++) fscanf(f, "%d ", &arr2[i]);

    fclose(f);

    printf("Array 1: ");
    for (i = 0; i < n; i++) printf("%d ", arr1[i]);
    printf("\nArray 1 size: %lu\n", n);
    printf("Array 2: ");
    for (i = 0; i < m; i++) printf("%d ", arr2[i]);
    printf("\nArray 2 size: %lu\n", m);

    int* combined = (int *)malloc((n+m) * sizeof(int));
    i = 0;
    int j = 0;
    int k = 0;
    while (i < n && j < m){
        if (arr1[i] < arr2[j]) combined[k++] = arr1[i++];
        else combined[k++] = arr2[j++];
    }
    while (i < n) combined[k++] = arr1[i++];
    while (j < m) combined[k++] = arr2[j++];

    printf("Combined array: ");
    for (i = 0; i < n + m; i++) printf("%d ", combined[i]);
    printf("\nCombined array size: %lu\n", n + m);

    free(arr1);
    free(arr2);
    free(combined);

    return 0;
}