// Walker Bagley

#include <stdio.h>
#include <math.h>

float avg(int[],int);
float stdev(int[],int);

int main()
{
    int grades[] =
    { 96,73,62,87,80,63,93,79,71,99,
      82,83,80,97,89,82,93,92,95,89,
      71,97,91,95,63,81,76,98,64,86,
      74,79,98,82,77,68,87,70,75,97,
      71,94,68,87,79 };

    int size = sizeof(grades) / sizeof(grades[0]);
    printf("Number of grades: %d\n",size);
    printf("Average: %0.2f\n",avg(grades,size));
    printf("Standard Deviation: %0.2f\n",stdev(grades,size));
  
  return 0;
}

// returns the average of the values in an array of grades
float avg(int g[], int s){
    int sum = 0;
    for (int i = 0; i < s; i++){
        sum += g[i];
    }
    return sum / s;
}
// returns the standard deviation of an array
float stdev(int g[],int s){
    float average = avg(g, s);
    float res = 0;
    for (int i = 0; i < s; i++){
        res += pow(g[i]-average,2);
    }
    return sqrt(res / s);
}