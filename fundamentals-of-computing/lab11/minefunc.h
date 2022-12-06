// Walker Bagley
// CSE 20311 Lab 11
// minefunc.h

// constants for board/screen/array size
#define LEN 850
#define NUM_CELLS 25
#define CELL_SIZE 25
#define DIFF 15

typedef struct Cell {
    int n; // number of neighboring cells that are bombs, -1 if it is a bomb
    int v; // 1 if the cell is visible, 0 if it is not
    int f; // 1 if the cell is flagged, 0 if it is not
    char r[2]; // char representing the cell when it is uncovered
} Cell;

void initGame(Cell b[NUM_CELLS][NUM_CELLS]);
void initNeighbors(Cell b[NUM_CELLS][NUM_CELLS]);

int updateStatus(Cell b[NUM_CELLS][NUM_CELLS]);
void displayBoard(Cell b[NUM_CELLS][NUM_CELLS]);

int numNeighbors(int x, int y, Cell b[NUM_CELLS][NUM_CELLS]);
void showBombs(Cell b[NUM_CELLS][NUM_CELLS]);

void openCell(int x, int y, Cell b[NUM_CELLS][NUM_CELLS]);
void flagCell(int x, int y, Cell b[NUM_CELLS][NUM_CELLS]);