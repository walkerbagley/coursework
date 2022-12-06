#include <stdio.h>

int main () {
    int x, y;
    printf("X: ");
    scanf("%d",&x);
    printf("Y: ");
    scanf("%d",&y);

    for (int i = 0; i <= y; i++){
        if (i == 1){
            for (int j = 0; j <= x; j++){
                if (j == 0){
                    printf("     ");
                }
                else{
                    printf("-----");
                }
            }
            printf("\n");
        }
        for (int j = 0; j <= x; j++){
            if (j == 0 && i > 0){
                printf("%4d |", i);
            }
            else if (i == 0){
                if (j == 0){
                    printf("  *   ");
                }
                else{
                    printf("%4d ", j);
                }
            }
            else{
                printf("%4d ",i * j);
            }
        }
        printf("\n");
    }

    return 0;
}