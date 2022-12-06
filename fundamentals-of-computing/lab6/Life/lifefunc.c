// Walker Bagley
// CSE 20311 Lab 6
// lifefunc.c

#include <stdio.h>
#include "lifefunc.h"

#define SIZE 40

// Prints the board with a border given the 2d array of chars representing the board
void printBoard(char board[SIZE][SIZE]){
    int i, j;
    for (i = -1; i <= SIZE; i++){
        for (j = -1; j <= SIZE; j++){
            if (i == -1 || i == SIZE){
                printf("-");
            }
            else if (j == -1 || j == SIZE){
                printf("|");
            }
            else{
                printf("%c", board[i][j]);
            }
        }
        printf("\n");
    }
}

// Adds a cell at a specified point to the array representing the board
void addCell(char board[SIZE][SIZE], int x, int y){
    board[x][y] = 'x';
}

// Removes a cell at a specified point from the array representing the board
void removeCell(char board[SIZE][SIZE], int x, int y){
    board[x][y] = ' ';
}

// Advances the board to the next state and stores that state in future according to the rules of the game
void nextIteration(char board[SIZE][SIZE], char future[SIZE][SIZE]){
    int i, j;
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            int n = numNeighbors(board, i, j);
            if (board[i][j] == ' ' && n == 3){
                future[i][j] = 'x';
            }
            else if (n != 2 && n != 3){
                future[i][j] = ' ';
            }
        }
    }
}

// Updates the second argument array to be equal to the first
void updateBoard(char a[SIZE][SIZE], char b[SIZE][SIZE]){
    int i, j;
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            b[i][j] = a[i][j];
        }
    }
}

// Counts the number of neighboring cells at any given point on the board
int numNeighbors(char board[SIZE][SIZE], int x, int y){
    int xmin, xmax, ymin, ymax;
    xmin = x == 0 ? 0 : x - 1;
    ymin = y == 0 ? 0 : y - 1;
    xmax = x == SIZE - 1 ? SIZE : x + 2;
    ymax = y == SIZE - 1 ? SIZE : y + 2;
    int i, j;
    int count = board[x][y] == 'x' ? -1 : 0;
    for (i = xmin; i < xmax; i++){
        for (j = ymin; j < ymax; j++){
            if (board[i][j] == 'x'){
                count++;
            }
        }
    }
    return count;
}