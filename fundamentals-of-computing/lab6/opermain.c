#include <stdio.h>
#include "operfn.h"

int main()
{
  float x, y;

  printf("enter two non-zero numbers: ");
  scanf("%f %f", &x, &y);
    // random useless comment
  showinfo(x, y);

  return 0;
}