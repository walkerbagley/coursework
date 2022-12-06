// Walker Bagley
// CSE 20311 Lab 7
// pathfunc.h

// Definition of Point struct here since this file is imported to the two others already
struct Point {
    double x;
    double y;
};

double pathLength(struct Point, struct Point);
double totalLength(struct Point[], int);