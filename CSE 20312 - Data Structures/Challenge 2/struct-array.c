/* Title: struct-array.c
 * Abstract: This program reads in a gradebook for students in a class and outputs each student's average score for the 5 quizzes. The program is setup with a student struct to structure the data.
 * Author: Walker Bagley
 * Email: wbagley@nd.edu
 * Estimate: 30 min
 * Date: 9/11/2022
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct student{
    char name[10];
    int id;
    double q1, q2, q3, q4, q5;
    double avg;
} student;

int main(void){
    char fileName[20];
    printf("Enter filename: ");
    fscanf(stdin, "%s", fileName);
    FILE* f = fopen(fileName, "r");
    if (f == NULL){
        printf("File does not exist.\n");
        return 0;
    }

    long unsigned int n;
    fscanf(f, "%lu\n", &n);
    student s[30];
    int i;
    for (i = 0; i < n; i++){
        fscanf(f, "%s ", s[i].name);
        fscanf(f, "%d ", &s[i].id);
        fscanf(f, "%lf ", &s[i].q1);
        fscanf(f, "%lf ", &s[i].q2);
        fscanf(f, "%lf ", &s[i].q3);
        fscanf(f, "%lf ", &s[i].q4);
        fscanf(f, "%lf\n", &s[i].q5);
        s[i].avg = (s[i].q1 + s[i].q2 + s[i].q3 + s[i].q4 + s[i].q5) / 5;
    }

    fclose(f);

    printf("------------------------------------------------\n  Course Report: Quiz Average\n------------------------------------------------\n");
    for (i = 0; i < n; i++) printf("  %s (%d): %.3lf\n", s[i].name, s[i].id, s[i].avg);
    printf("------------------------------------------------\n");

    return 0;
}