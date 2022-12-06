#include <stdio.h>
#include <math.h>

int main() {
    double s1;
    double s2;
    double angle;
    printf("This will compute the Law of Cosines.\nSide 1 length: ");
    scanf("%lf",&s1);
    printf("Side 2 length: ");
    scanf("%lf",&s2);
    printf("Angle (degrees): ");
    scanf("%lf",&angle);

    double s3 = sqrt(pow(s1, 2) + pow(s2, 2) - 2 * s1 * s2 * cos(angle*M_PI/180));

    printf("\nThird side length: %lf\n",s3);

    return 0;
}