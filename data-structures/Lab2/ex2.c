/* Title: ex2.c
 * Abstract: FILL IN
 * Author: Walker Bagley
 * Email: wbagley@nd.edu
 * Estimate: 15 min
 * Date: 8/30/2022
 */
#include <stdio.h>
#include <stdlib.h>

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
    int i;
    fprintf(stdout, "Array values:");
    for(i = 0; i < n; i++){
        fprintf(stdout, " %d", nums[i]);
    }

    for(i = n; i > 0; i--){
        nums[i] = nums[i-1];
    }
    nums[0] = 0;

    fprintf(stdout, "\nArray values after right shift:");
    for(i = 0; i < n; i++){
        fprintf(stdout, " %d", nums[i]);
    }

    fprintf(stdout, "\n");

    fclose(f);
    free(nums);
    
    return 0;
}
