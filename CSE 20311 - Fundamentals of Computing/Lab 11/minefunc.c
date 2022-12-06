// Walker Bagley
// CSE 20311 Lab 11
// minefunc.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "minefunc.h"
#include "gfx2.h"

void initGame(Cell b[NUM_CELLS][NUM_CELLS]){
    int i, j;
    srand(time(0));
    for (i = 0; i < NUM_CELLS; i++){
        for (j = 0; j < NUM_CELLS; j++){
            b[i][j].v = 0;
            b[i][j].f = 0;
            if (rand() % 100 + 1 < DIFF){
                b[i][j].n = -1;
                strcpy(b[i][j].r, "x");
            }
            else {
                b[i][j].n = 0;
                strcpy(b[i][j].r, "-");
            }
        }
    }
}

void initNeighbors(Cell b[NUM_CELLS][NUM_CELLS]){
    int i, j;
    for (i = 0; i < NUM_CELLS; i++){
        for (j = 0; j < NUM_CELLS; j++){
            if (b[i][j].n != -1){
                b[i][j].n = numNeighbors(i, j, b);
                if (b[i][j].n != 0) sprintf(b[i][j].r, "%d", b[i][j].n);
            }
        }
    }
}

int updateStatus(Cell b[NUM_CELLS][NUM_CELLS]){
    int n = 1;
    int i, j;
    for (i = 0; i < NUM_CELLS; i++){
        for (j = 0; j < NUM_CELLS; j++){
            if (b[i][j].v && b[i][j].n == -1) return 2;
            else if (!b[i][j].v && b[i][j].n >= 0) n = 0;
        }
    }
    return n;
}

void displayBoard(Cell b[NUM_CELLS][NUM_CELLS]){
    gfx_clear();
    int margin = (LEN - CELL_SIZE * NUM_CELLS) / 2;
    int i, j;
    for (i = 0; i < NUM_CELLS; i++){
        for (j = 0; j < NUM_CELLS; j++){
            gfx_rectangle(margin+CELL_SIZE*i, margin/2+CELL_SIZE*j, CELL_SIZE, CELL_SIZE);
            if (b[i][j].v){
                gfx_text(margin+(2*CELL_SIZE/5)+CELL_SIZE*i, margin/2+(3*CELL_SIZE/4)+CELL_SIZE*j, b[i][j].r);
            }
            else if (b[i][j].f){
                gfx_fill_rectangle(margin+CELL_SIZE*i+4*CELL_SIZE/10, margin/2+CELL_SIZE*j+4*CELL_SIZE/10, CELL_SIZE/4, CELL_SIZE/4);
            }
        }
    }
}

int numNeighbors(int x, int y, Cell b[NUM_CELLS][NUM_CELLS]){
    int xmin = x == 0 ? 0 : x - 1;
    int xmax = x >= NUM_CELLS - 1 ? NUM_CELLS : x + 2;
    int ymin = y == 0 ? 0 : y - 1;
    int ymax = y >= NUM_CELLS - 1 ? NUM_CELLS : y + 2;
    int n = 0;
    int i, j;

    for (i = xmin; i < xmax; i++){
        for (j = ymin; j < ymax; j++){
            if (b[i][j].n == -1) n++;
        }
    }
    return n;
}

void showBombs(Cell b[NUM_CELLS][NUM_CELLS]){
    int i, j;
    for (i = 0; i < NUM_CELLS; i++){
        for (j = 0; j < NUM_CELLS; j++){
            if (b[i][j].n == -1) b[i][j].v = 1;
        }
    }
}

void openCell(int x, int y, Cell b[NUM_CELLS][NUM_CELLS]){
    if (b[x][y].f == 1) return;
    b[x][y].v = 1;
    int xmin = x == 0 ? 0 : x - 1;
    int xmax = x >= NUM_CELLS - 2 ? NUM_CELLS : x + 2;
    int ymin = y == 0 ? 0 : y - 1;
    int ymax = y >= NUM_CELLS - 2 ? NUM_CELLS : y + 2;
    int i, j;
    for (i = xmin; i < xmax; i++){
        for (j = ymin; j < ymax; j++){
            if (b[i][j].n == 0 && b[i][j].v == 0) openCell(i, j, b);
            else if (b[i][j].n > 0 && b[i][j].f == 0) b[i][j].v = 1;
        }
    }
}

void flagCell(int x, int y, Cell b[NUM_CELLS][NUM_CELLS]){
    if (b[x][y].f) b[x][y].f = 0;
    else b[x][y].f = 1;
}