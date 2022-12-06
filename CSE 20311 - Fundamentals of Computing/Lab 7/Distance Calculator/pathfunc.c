// Walker Bagley
// CSE 20311 Lab 7
// pathfunc.c

#include <math.h>
#include "pathfunc.h"

// Helper function to calculate the distance between two Point structs
double pathLength(struct Point a, struct Point b){
    double x1 = a.x;
    double x2 = b.x;
    double y1 = a.y;
    double y2 = b.y;

    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

// Function that uses pathLength and iterates over an array of points, summing the distances
double totalLength(struct Point p[], int n){
    int i;
    double sum = 0;
    for (i = 0; i < n - 1; i++){
        sum += pathLength(p[i], p[i + 1]);
    }
    return sum;
}
