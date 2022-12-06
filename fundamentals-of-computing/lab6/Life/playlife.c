// Walker Bagley
// CSE 20311 Lab 6
// playlife.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lifefunc.h"

#define SIZE 40

int main (int argc, char **argv){
    // Read file input if present
    FILE *f;
    if (argc == 2){
        f = fopen(argv[1], "r");
    }
    else if (argc > 2){
        printf("ERROR: Too many inputs.");
        return 1;
    }

    // Initialize board
    char board[SIZE][SIZE];
    char future[SIZE][SIZE];
    int i, j;
    for (i = 0; i < SIZE; i++){
        for (j = 0; j < SIZE; j++){
            board[i][j] = ' ';
            future[i][j] = ' ';
        }
    }

    // While loop with switch cases for characters
    while (1) {
        // Taking user input for each move
        char entry[8];
        if (!f){
            fgets(entry, 8, stdin);
        }
        else {
            fgets(entry, 8, f);
        }
        char o = entry[0];
        char trash[1], i[3], j[3];
        int x, y;
        switch (o){
            // Adding a cell
            case 'a':
                system("clear");
                sscanf(entry, "%c %s %s", trash, i, j);
                y = atoi(i);
                x = atoi(j);
                addCell(future, x, y);
                updateBoard(future, board);
                printBoard(board);
                break;

            // Removing a cell
            case 'r':
                system("clear");
                sscanf(entry, "%c %s %s", trash, i, j);
                y = atoi(i);
                x = atoi(j);
                removeCell(future, x, y);
                updateBoard(future, board);
                printBoard(board);
                break;

            // Moving to the next iteration
            case 'n':
                system("clear");
                nextIteration(board, future);
                updateBoard(future, board);
                printBoard(board);
                break;

            // Quitting the program
            case 'q':
                return 1;
                break;

            // Running the game until it ends
            case 'p':
                while (1){
                    usleep(200000);
                    system("clear");
                    nextIteration(board, future);
                    updateBoard(future, board);
                    printBoard(board);
                }
                break;
        }
    }
    return 0;
}
