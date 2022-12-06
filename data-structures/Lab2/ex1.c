/* Title: ex1.c
 * Abstract: FILL IN
 * Author: Walker Bagley
 * Email: wbagley@nd.edu
 * Estimate: 10 min
 * Date: 8/30/2022
 */
#include <stdio.h>

int main(void){

    FILE* f1 = fopen("input1.txt", "r");

    if (f1 == NULL) {
        printf("File does not exist!");
        return 0;
    }

    int n;
    while (!feof(f1)){
        fscanf(f1, "%d", &n);
        fprintf(stdout, "Value: %d\n", n);
    }

    fclose(f1);

    FILE* f2 = fopen("output1.txt", "w");

    fprintf(f2, "I successfully wrote to a file!\n");

    fclose(f2);
    
    return 0;
}
