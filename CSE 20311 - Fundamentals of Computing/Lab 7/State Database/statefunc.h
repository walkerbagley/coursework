// Walker Bagley
// CSE 20311 Lab 7
// statefunc.h

#define STR_LEN 30
#define MAX_ST 100

// State struct definition
typedef struct State {
    char abbr[3];
    char name[STR_LEN];
    char capital[STR_LEN];
    int year;
} State;

// Function headers
void printMenu();
void printData(State[], int);
int locateState(State[], int, char[]);
int stateYears(State[], State[], int, int, int);
void orderStates(State[], State[], int);
void printBar(State[], int, int);