// Walker Bagley
// CSE 20311 Lab 8
// cwfunc.h

#define WORD_LEN 15
#define NUM_WORDS 20

// struct for each word to be placed in the crossword
typedef struct {
    char word[WORD_LEN];    // contains the word
    char clue[WORD_LEN];    // contains the scrambled clue/anagram
    int inPuzzle;       // stores 1 if the word was placed, 0 if it wasn't
    int orient;         // stores 0 for no placement, 1 for across, 2 for down
    int loc[2];         // stores the coordinates of the start of the word
} Word;

void boardInit(char[WORD_LEN][WORD_LEN], char[WORD_LEN][WORD_LEN]);

int getWords(Word[NUM_WORDS], int, char[]);
int processWord(char[WORD_LEN]);

void sortWords(Word[NUM_WORDS], int);
void sortClues(Word[NUM_WORDS], int);

void generate(char[WORD_LEN][WORD_LEN], Word[NUM_WORDS], int);
int locateWord(char[WORD_LEN][WORD_LEN], Word, int[4]);
int neighbors(char[WORD_LEN][WORD_LEN], int, int);
int wordFit(char[WORD_LEN][WORD_LEN], Word, int, int, int, int);

void setPuzzle(char[WORD_LEN][WORD_LEN], char[WORD_LEN][WORD_LEN]);
void makeClues(Word[NUM_WORDS], int);
void printBoard(char[WORD_LEN][WORD_LEN], int, FILE *);
void printClues(Word[NUM_WORDS], int, int, FILE *);

void output(char[WORD_LEN][WORD_LEN], char[WORD_LEN][WORD_LEN], Word[NUM_WORDS], int, int, char[]);