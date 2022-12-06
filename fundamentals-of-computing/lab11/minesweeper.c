// Walker Bagley
// CSE 20311 Lab 11
// minesweeper.c

#include <stdio.h>
#include <unistd.h>
#include "minefunc.h"
#include "gfx2.h"

int main(){
    int status = 0; // 0 for in play, 1 for win, 2 for loss, 3 for exit
    gfx_open(LEN, LEN, "Minesweeper");
    int margin = (LEN - CELL_SIZE * NUM_CELLS) / 2;

    gfx_text(LEN/2 - 70, LEN/2-100, "Welcome to Minesweeper");
    gfx_text(LEN/2 - 110, LEN/2-40, "Spacebar places a flag on the mouse");
    gfx_text(LEN/2 - 110, LEN/2-20, "Left click opens a cell");
    gfx_text(LEN/2 - 110, LEN/2, "q quits the game");
    gfx_text(LEN/2 - 80, LEN/2+60, "Press any key to continue");

    gfx_wait();
    gfx_flush();

    Cell board[NUM_CELLS][NUM_CELLS];
    initGame(board);
    initNeighbors(board);

    while (!status){
        displayBoard(board);
        switch (gfx_wait()){
            case 'q':
                status = 3;
                break;
            case 1:
                openCell((gfx_xpos() - margin) / CELL_SIZE, (gfx_ypos() - margin/2) / CELL_SIZE, board);
                status = updateStatus(board);
                break;
            case ' ':
                flagCell((gfx_xpos() - margin) / CELL_SIZE, (gfx_ypos() - margin/2) / CELL_SIZE, board);
                status = updateStatus(board);
                break;
            default:
                break;
        }
        gfx_flush();
    }
    gfx_clear();
    showBombs(board);
    displayBoard(board);
    gfx_flush();

    if (status == 1){
        gfx_text(LEN/2 - 70, margin+NUM_CELLS*CELL_SIZE, "Congratulations! You won!");
    }
    else if (status == 2){
        gfx_text(LEN/2 - 40, margin+NUM_CELLS*CELL_SIZE, "Oops! You lost!");
    }
    gfx_text(LEN/2 - 60, margin+NUM_CELLS*CELL_SIZE+15, "Press any key to exit.");
    gfx_wait();
    return 0;
}