#include <stdio.h>
#include <math.h>

int main () {
    double xmin = 0;
    double xmax = 10;
    double y;

    double maxx, maxy = 0;
    double minx, miny = 100;

    printf("\nPlot for y = cos(x^2/5) - sin(x/2) + 2 for x from %.2f to %.2f\n  X      Y\n", xmin, xmax);
    for (double x = xmin; x < xmax; x += 0.2){
        y = cos(pow(x, 2) / 5) - sin(x / 2) + 2;
        if (y > maxy){
            maxx = x;
            maxy = y;
        }
        else if (y < miny) {
            minx = x;
            miny = y;
        }
        printf("%5.2f   %4.2f   ", x, y);
        for (double i = 0; i <= y; i += 0.15){
            printf("#");
        }
        printf("\n");
    }
    printf("\nThe maximum of %.2f was at %.2f\nThe minimum of %.2f was at %.2f\n\n", maxy, maxx, miny, minx);

    return 0;
}