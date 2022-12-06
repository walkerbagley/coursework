#include <stdio.h>
#include <math.h>

int main () {
    int squares = 0;
    double roots = 0;

    for (int i = 1; i <= 10; i += 1)
    {
        squares += pow(i, 2);
        roots += sqrt(i);
    }

    printf("Sum of Squares: %i\nSum of Square Roots: %lf\n",squares, roots);

    return 0;
}