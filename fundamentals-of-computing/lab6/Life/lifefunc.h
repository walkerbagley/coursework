// Walker Bagley
// CSE 20311 Lab 6
// lifefunc.h

#define SIZE 40

void printBoard(char[SIZE][SIZE]);
void addCell(char[SIZE][SIZE], int, int);
void removeCell(char[SIZE][SIZE], int, int);
void nextIteration(char[SIZE][SIZE], char[SIZE][SIZE]);

void updateBoard(char[SIZE][SIZE], char[SIZE][SIZE]);
int numNeighbors(char[SIZE][SIZE], int, int);