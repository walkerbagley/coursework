// Walker Bagley

#import <stdio.h>

void yrs_winning_record (int[], int[], int);
void yrs_with_wins (int[], int, int);
void yrs_with_losses (int[], int, int);
void yrs_undefeated (int[], int);
void win_rate (int[], int[], int, int);
void win_loss_count (int[], int[], int, int);
void avg_wins (int[], int, int);

int main(){
    int wins[] = 
    {   6, 8, 6, 8, 5, 5, 6, 6, 8, 7, 4,
        6, 7, 7, 6, 7, 8, 6, 3, 9, 9, 10,
        8, 9, 10, 7, 9, 7, 5, 9, 10, 6, 6,
        3, 6, 7, 6, 6, 8, 7, 7, 8, 7, 9,
        8, 7, 8, 9, 9, 10, 4, 7, 7, 9, 9,
        8, 2, 7, 6, 5, 2, 5, 5, 2, 9, 7,
        9, 8, 7, 8, 10, 8, 8, 11, 10, 8, 9,
        11, 9, 7, 9, 5, 6, 7, 7, 5, 5, 8,
        12, 12, 9, 10, 10, 11, 6, 9, 8, 7, 9,
        5, 9, 5, 10, 5, 6, 9, 10, 3, 7, 6,
        8, 8, 12, 9, 8, 10, 4, 10, 12, 11, 10, 11 };
    int losses[] = 
    {   3, 1, 2, 0, 3, 4, 1, 0, 1, 0, 1,
        0, 0, 0, 2, 1, 1, 1, 1, 0, 0, 1,
        1, 1, 0, 2, 1, 1, 4, 0, 0, 2, 2,
        5, 3, 1, 2, 2, 1, 2, 2, 0, 2, 1,
        2, 2, 0, 0, 0, 0, 4, 2, 2, 0, 1,
        2, 8, 3, 4, 5, 8, 5, 5, 7, 1, 2,
        0, 2, 2, 2, 1, 2, 3, 0, 2, 3, 3,
        1, 3, 4, 2, 6, 4, 5, 5, 6, 6, 4,
        0, 1, 3, 3, 1, 1, 5, 3, 3, 6, 3,
        7, 3, 6, 3, 7, 6, 3, 3, 9, 6, 6,
        5, 5, 1, 4, 5, 3, 8, 3, 1, 2, 2, 2 };
    int len = sizeof wins / sizeof wins[0];
    int choice = 0;
    while (choice != 8){
        printf("\n1 - Show years with a winning record\n2 - Show years with >=n wins\n3 - Show years with >=n losses\n4 - Show undefeated years\n5 - Show win rate between two specific years\n6 - Wins and losses between two specific years\n7 - Average number of wins per season between two specific years\n8 - Quit\nEnter your selection: ");
        scanf("%d", &choice);
        int n, a, b = 0;
        switch (choice){
            case 1:
                yrs_winning_record(wins, losses, len);
                break;
            case 2:
                printf("Enter minimum number of wins: ");
                scanf("%d", &n);
                yrs_with_wins(wins, n, len);
                break;
            case 3:
                printf("Enter minimum number of losses: ");
                scanf("%d", &n);
                yrs_with_losses(losses, n, len);
                break;
            case 4:
                yrs_undefeated (losses, len);
                break;
            case 5:
                printf("Enter starting year: ");
                scanf("%d", &a);
                printf("Enter ending year: ");
                scanf("%d", &b);
                win_rate(wins, losses, a, b);
                break;
            case 6:
                printf("Enter starting year: ");
                scanf("%d", &a);
                printf("Enter ending year: ");
                scanf("%d", &b);
                win_loss_count(wins, losses, a, b);
                break;
            case 7:
                printf("Enter starting year: ");
                scanf("%d", &a);
                printf("Enter ending year: ");
                scanf("%d", &b);
                avg_wins(wins, a, b);
                break;
            case 8:
                break;
            default:
                printf("Invalid entry.\n");
                break;
        }
    }
    return 0;
}

// This function prints the years with a winning record
void yrs_winning_record (int w[], int l[], int len){
    printf("\nYears with a winning record: \n");
    int count = 0;
    for (int i = 0; i < len; i++){
        if (w[i] > l[i]){
            printf("%5d", i + 1900);
            count++;
            if (count % 10 == 0){
                printf("\n");
            }
        }
    }
    printf("\n");
}
// This function prints the years with n or more wins
void yrs_with_wins (int w[], int n, int len){
    printf("\nYears with %d or more wins: \n", n);
    int count = 0;
    for (int i = 0; i < len; i++){
        if (w[i] >= n){
            printf("%5d", i + 1900);
            count++;
            if (count % 10 == 0){
                printf("\n");
            }
        }
    }
    printf("\n");
}
// This function prints the years with n or more losses
void yrs_with_losses (int l[], int n, int len){
    printf("\nYears with %d or more losses: \n", n);
    int count = 0;
    for (int i = 0; i < len; i++){
        if (l[i] >= n){
            printf("%5d", i + 1900);
            count++;
            if (count % 10 == 0){
                printf("\n");
            }
        }
    }
    printf("\n");
}
// This function prints the years with 0 losses, aka undefeated seasons
void yrs_undefeated (int l[], int len){
    printf("\nYears undefeated: \n");
    int count = 0;
    for (int i = 0; i < len; i++){
        if (l[i] == 0){
            printf("%5d", i + 1900);
            count++;
            if (count % 10 == 0){
                printf("\n");
            }
        }
    }
    printf("\n");
}
// This function prints win rate as a percentage between two years
void win_rate (int w[], int l[], int a, int b){
    int min = a - 1900;
    int max = b - 1900;
    float wins, losses = 0;
    for (int i = min; i <= max; i++){
        wins += w[i];
        losses += l[i];
    }
    printf("\nNotre Dame football had a win rate of %.2f%% between %d and %d.\n", (wins*100)/(wins+losses), a, b);
}
// This function prints the record between two years
void win_loss_count (int w[], int l[], int a, int b){
    int min = a - 1900;
    int max = b - 1900;
    int wins, losses = 0;
    for (int i = min; i <= max; i++){
        wins += w[i];
        losses += l[i];
    }
    printf("\nNotre Dame football had a record of %d-%d between %d and %d.\n", wins, losses, a, b);
}
// This function prints average wins per season between two years
void avg_wins (int w[], int a, int b){
    int min = a - 1900;
    int max = b - 1900;
    float wins = 0;
    for (int i = min; i <= max; i++){
        wins += w[i];
    }
    printf("\nNotre Dame football had an average of %.2f wins per season between %d and %d.\n", wins/(b-a), a, b);
}