#import <stdio.h>
#import <math.h>
#import <stdbool.h>

void printMenu(void);
double multiplication(double x, double y);
double division(double x, double y);
double exponent(double x, double y);
double root(double x, double y);

int main(){
    bool run = true;
    int choice = 0;

    while (run){
        printMenu();
        scanf("%d", &choice);
        if (choice == 5){
            run = false;
            printf("Goodbye!\n");
        }
        else{
            double x, y;
            printf("Enter two numbers: ");
            scanf("%lf %lf", &x, &y);
            if (choice == 1){
                printf("%0.2lf x %0.2lf = %0.2lf\n", x, y, multiplication(x, y));
            }
            else if (choice == 2){
                printf("%0.2lf / %0.2lf = %0.2lf\n", x, y, division(x, y));
            }
            else if (choice == 3){
                printf("%0.2lf ^ %0.2lf = %0.2lf\n", x, y, exponent(x, y));
            }
            else if (choice == 4){
                printf("%0.2lf ^ (1 / %0.2lf) = %0.2lf\n", x, y, root(x, y));
            }

        }
    }

    return 0;
}

void printMenu(){
    printf("Select an option:\n 1 for multiplication\n 2 for division\n 3 for exponent\n 4 for root\n 5 to exit\nEnter your choice: ");
}
double multiplication(double x, double y){
    return x * y;
}
double division(double x, double y){
    if (y != 0){
        return x / y;
    }
    else {
        printf("ERROR: Cannot divide by 0.");
    }
}
double exponent(double x, double y){
    return pow(x, y);
}
double root(double x, double y){
    if (y != 0){
        return pow(x, 1/y);
    }
    else {
        printf("ERROR: Cannot have the root of 0.");
    }
}