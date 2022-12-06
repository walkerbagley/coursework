// Walker Bagley

#import <stdio.h>

int main(){
    int arr[5];
    printf("Enter 5 integers: ");
    scanf("%d %d %d %d %d", &arr[0], &arr[1], &arr[2], &arr[3], &arr[4]);
    printf("%d %d %d %d %d\n", arr[4], arr[3], arr[2], arr[1], arr[0]);
    
    return 0;
}