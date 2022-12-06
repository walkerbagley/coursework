#include <stdio.h>
#include <math.h>

double determinant(double a, double b, double c);

int main () {
    double a, b, c, x1, x2, det = 1;

    while (det != 0 && a != 0){
        printf("Enter a, b, and c: ");
        scanf("%lf %lf %lf", &a, &b, &c);
        det = determinant(a, b, c);
        if (det >= 0 && a != 0){
            x1 = (b + det) / (2*a);
            x2 = (b - det) / (2*a);
            printf("x1: %0.2lf\nx2: %0.2lf\n", x1, x2);
        }
        else {
            printf("No real solutions.");
        }
    }

    return 0;
}

double determinant(double a, double b, double c){
    return pow(b, 2) - 4*a*c;
}