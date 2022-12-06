// Walker Bagley
// CSE 20311 Lab 7
// usastates.c

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "statefunc.h"

int main (int argc, char *argv[]){
    // File initialization and reading from command line if necessary
    FILE *f;
    if (argc == 1){
        char filename[STR_LEN];
        printf("Enter a file name: ");
        fgets(filename, STR_LEN, stdin);
        filename[strlen(filename)-1] = '\0';
        f = fopen(filename, "r");
    }
    else if (argc == 2){
        f = fopen(argv[1], "r");
    }
    else {
        printf("ERROR: Invalid input.");
        return 1;
    }

    // Making sure the file exists
    if (!f) {
        printf("ERROR: Invalid file name.\n");
        return 1;
    }

    // Preparation to read in each state
    State states[MAX_ST];
    int count = 0;

    // Read in each line of the csv as a state by tokenizing the line by comma
    while (!feof(f)) {
        char row[MAX_ST];
        char *token;
        fgets(row, MAX_ST, f);
        token = strtok(row, ",");
        strcpy(states[count].abbr, token);
        token = strtok(NULL, ",");
        strcpy(states[count].name, token);
        token = strtok(NULL, ",");
        strcpy(states[count].capital, token);
        token = strtok(NULL, ",");
        states[count].year = atoi(token);
        count++;
    }

    // Main loop of the program
    while (1){
        // Variable initialization
        char choice[3];
        char ab[3];
        char temp[STR_LEN];
        int s;

        // Get user input for selected option
        printMenu();
        fgets(choice, 3, stdin);
        int c = 0;
        sscanf(choice, "%d", &c);

        // Switch with option cases
        switch (c){
            // Print all of the data
            case 1:{
                printData(states, count);
                break;
            }

            // Lookup state by abbreviation and display its info
            case 2:{
                printf("Enter an abbreviation: ");
                fgets(ab, 3, stdin);
                fflush(stdin);
                ab[0] = toupper(ab[0]);
                ab[1] = toupper(ab[1]);
                State new[1] = {states[locateState(states, count, ab)]};
                printData(new, 1);
                break;
            }

            // Lookup state by name and display its capital
            case 3:{
                printf("Enter a name: ");
                fgets(temp, STR_LEN, stdin);
                temp[strlen(temp)-1] = '\0';
                temp[0] = toupper(temp[0]);
                fflush(stdin);
                printf("\nThe capital of %s is %s.\n", temp, states[locateState(states, count, temp)].capital);
                break;
            }

            // Display all states that entered the union in a given year
            case 4:{
                printf("Enter a year: ");
                fgets(temp, STR_LEN, stdin);
                temp[strlen(temp)-1] = '\0';
                fflush(stdin);
                int n = atoi(temp);
                State year[MAX_ST];
                s = stateYears(states, year, count, n, n);
                printf("\nThere were %d states that joined the union in %d.\n", s, n);
                printData(year, s);
                break;
            }

            // Display all states that entered the union between 2 given years
            case 5:{
                printf("Enter two years separated by a space: ");
                fgets(temp, STR_LEN, stdin);
                temp[strlen(temp)-1] = '\0';
                fflush(stdin);
                int min, max;
                sscanf(temp, "%d %d", &min, &max);
                State years[MAX_ST];
                s = stateYears(states, years, count, min, max);
                printf("\nThere were %d states that joined the union between %d and %d.\n", s, min, max);
                printData(years, s);
                break;
            }

            // Display the states in order of year joined
            case 6:{
                State ordered[MAX_ST];
                orderStates(states, ordered, count);
                printData(ordered, count);
                break;
            }

            // Print bar graph of year joined with given bins
            case 7:{
                printf("Enter number of bins: ");
                fgets(ab, 3, stdin);
                fflush(stdin);
                int bins = 0;
                sscanf(ab, "%d", &bins);
                printBar(states, count, bins);
                break;
            }
            // Quit program
            case 8:{
                return 2;
                break;
            }

            default:{
                printf("Enter a valid choice.\n");
                break;
            }
        }
    }
    return 0;
}