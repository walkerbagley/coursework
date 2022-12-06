// Walker Bagley
// CSE 20311 Lab 7
// path.c

#include <stdio.h>
#include "pathfunc.h"

int main (int argc, char *argv[]){
    
    // If a single file with points is passed into the program via argv, run the program, otherwise print an error and exit
    if (argc == 2){
        // File declaration and opening
        FILE *f;
        f = fopen(argv[1], "r");

        // Initializing array of Point structs
        struct Point points[30];
        int count = 0;

        // Reading in the sets of points to each struct
        while (!feof(f)) {
            fscanf(f, "%lf %lf\n", &points[count].x, &points[count].y);
            count++;
        }

        // Printing the table of points
        printf("\nThere are %d points:\n\n   x  |  y   \n------|------\n", count);
        int i;
        for (i = 0; i < count; i++){
            printf("%5g | %5g\n", points[i].x, points[i].y);
        }

        // Summing and then printing the total length
        double length = totalLength(points, count);
        printf("\nThe path distance through them is %.2lf\n\n", length);
    }
    else {
        printf("ERROR: Invalid input.");
        return 1;
    }

    return 0;
}