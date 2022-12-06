// Walker Bagley

#import <stdio.h>

int main(){
    int primes[1001] = {0};
    int count = 0;
    for (int i = 2; i <= 1001; i++){
        if (primes[i] == 0){
            printf("%5d", i);
            count++;
            if (count % 10 == 0){
                printf("\n");
            }
            for (int j = i; j <= 1001; j++){
                if (j % i == 0){
                    primes[j] = 1;
                }
            }
        }
    }
    printf("\n");
    return 0;
}