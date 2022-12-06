/* Title: ex1.c
 * Abstract: TBD
 * Author: Walker Bagley
 * Email: wbagley@nd.edu
 * Estimate: TBD
 * Date: 9/6/2022
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Student{
    char name[10];
    double score1;
    double score2;
    double avg;
} Student;

int main(void){

    char fileName[100];
    fprintf(stdout, "Enter input file name: ");
    fscanf(stdin, "%s", &fileName);

    FILE* f = fopen(fileName, "r");

    if (f == NULL) {
        printf("File does not exist!");
        return 0;
    }

    Student s[2];

    int n = 0;
    while(!feof(f)){
        fscanf(f, "%s %lf %lf\n", &s[n].name, &s[n].score1, &s[n].score2);
        n++;
    }
    fclose(f);

    int i;
    for (i = 0; i < n; i++){
        s[i].avg = (s[i].score1 + s[i].score2) / 2;
        fprintf(stdout, "%s's average: %.1lf\n", s[i].name, s[i].avg);
    }

    if (s[0].avg >= s[1].avg) fprintf(stdout, "%s has a better score than %s.\n", s[0].name, s[1].name);
    else fprintf(stdout, "%s has a better score than %s.\n", s[1].name, s[0].name);

    return 0;
}