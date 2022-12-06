// Walker Bagley

#import <stdio.h>
#import <stdbool.h>

int main(){
    bool run = true;
    int count = 0;
    int arr[20];
    while (run){
        printf("Enter a number: ");
        int temp = 0;
        scanf("%d", &temp);
        if (temp == -1){
            run = false;
        }
        else {
            arr[count] = temp;
            count++;
        }
    }
    int final[count];
    for (int i = 0; i < count; i++){
        final[i] = arr[i];
    }
    for (int i = count - 1; i >= 0; i--){
        printf("%d ", final[i]);
    }
    printf("\n");
}