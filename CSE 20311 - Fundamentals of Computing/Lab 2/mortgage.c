#include <stdio.h>
#include <stdbool.h>

int main () {
    double principal, interest, payment, total = 0; 
    int months = 1;
    bool valid = true;
    while (valid)
    {
        printf("Principal: ");
        scanf("%lf",&principal);
        printf("Interest Rate (%%): ");
        scanf("%lf",&interest);
        printf("Desired Monthly Payment: ");
        scanf("%lf",&payment);
        if (interest > 0 && principal > 0 && payment > 0){
            valid = false;
        }
        else{
            printf("Error: Negative value entered.\n\n");
        }
    }

    if (payment < ((interest/1200)*principal)){
        printf("\nERROR: Desired monthly payment is less than interest.");
        return 1;
    }

    interest /= 1200;
    printf("\nMonth     Payment    Interest        Balance\n");

    while (principal > 0){
        if (principal < payment){
            printf("%5d     $%6.2lf     $%6.2lf     $%9.2lf\n", months, principal + interest * principal, interest * principal, principal - principal);
            total += principal+(interest/1200)*principal;
        }
        else {
            printf("%5d     $%6.2lf     $%6.2lf     $%9.2lf\n", months, payment, interest * principal, principal + interest * principal - payment);
            total += payment;
        }
        principal = principal + (interest / 1200) * principal - payment;
        months++;
    }

    printf("\nYou paid a total of $%.2lf over %d years and %d months.\n\n",total,(months-1)/12,(months-1)%12);

    return 0;
}