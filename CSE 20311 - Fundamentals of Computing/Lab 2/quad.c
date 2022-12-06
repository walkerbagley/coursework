// quad.c
// computes the roots of a quadratic equation
#include <stdio.h>
#include <math.h>

int main()
{
  double a, b, c, disc;
  double x1, x2;

  printf("Enter the coefficients (a,b,c) of a quadratic equation: ");
  scanf("%lf %lf %lf", &a, &b, &c);

  disc = pow(b, 2) - 4 * a * c;

  if (disc < 0){
      printf("No solutions.\n");
  }
  else if (disc == 0){./
      printf("x1: %lf\n", -b / (2 * a));
  }
  else{
      printf("x1: %lf\nx2: %lf\n", sqrt(-b+disc)/(2*a), sqrt(-b-disc)/(2*a));
  }

  return 0;
}
