// Walker Bagley
// CSE 20311 Lab 7
// statefunc.c

#include <stdio.h>
#include <string.h>
#include "statefunc.h"

// Function that prints the menu
void printMenu(){
    printf("\n1 - Show all data\n2 - Show state data based on abbreviation\n3 - Show capital based on name\n4 - Show states that joined in n year\n5 - Show states who joined between 2 years\n6 - Show states in order of joining\n7 - Show bar graph of years joined\n8 - Quit\nEnter your choice: ");
}

// Function that prints the data from a provided array of States
void printData(struct State s[], int n){
    if (n == 0){
        printf("\nNo states were found.\n");
    }
    else{
        printf("\n%4s | %15s | %15s | %4s\n-----------------------------------------------\n", "ABBR", "NAME", "CAPITAL", "YEAR");
        int i;
        for (i = 0; i < n; i++){
            printf("%4s | %15s | %15s | %4d\n", s[i].abbr, s[i].name, s[i].capital, s[i].year);
        }
    }
}

// Function that returns the index of a provided State name or abbreviation
int locateState(struct State s[], int n, char a[]){
    int i;
    for (i = 0; i < n; i++){
        if (strcmp(s[i].abbr, a) == 0 || strcmp(s[i].name, a) == 0){
            return i;
        }
    }
    return -1;
}

// Function that returns the number of states between 2 years, and modifies the new array to contain only the states within those 2 years
int stateYears(State old[], State new[], int n, int min, int max){
    int count = 0;
    int i;
    for (i = 0; i < n; i++){
        if (old[i].year >= min && old[i].year <= max){
            new[count] = old[i];
            count++;
        }
    }
    return count;
}

// Function that orders the States in a provided array and stores this order in a new array of States
void orderStates(State old[], State new[], int n){
    new[0] = old[0];
    int i, j;
    for (i = 1; i < n; i++){
        int loc = 0;
        for (j = 0; j < i; j++){
            if (new[j].year <= old[i].year) loc++;
        }
        for (j = i; j > loc; j--){
            new[j] = new[j - 1];
        }
        new[loc] = old[i];
    }
}

// Function that prints a bar graph with specified bins of the years States joined
void printBar(State s[], int n, int b){
    int yearData[b];
    int min = 10000;
    int max = 0;
    int i;
    for (i = 0; i < n; i++){
        if (s[i].year < min) min = s[i].year;
        if (s[i].year > max) max = s[i].year;
    }
    int binSize = (max - min) / (b - 1);
    for (i = 0; i < b; i++){
        yearData[i] = 0;
    }
    for (i = 0; i < n; i++){
        yearData[(s[i].year - min) / binSize] += 1;
    }
    printf("\n");
    for (i = 0; i < b; i++){
        printf("%d - %d | ", min + i*binSize, min + (i+1)*binSize);
        int j;
        for (j = 0; j < yearData[i]; j++) printf("*");
        printf("\n");
    }
}