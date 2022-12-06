// Walker Bagley
// CSE 20311 Lab 8
// cwfunc.c

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cwfunc.h"

// initializes two 2D arrays (boards) to be completely '.' and '#' for the empty crossword puzzle and answer arrays
void boardInit(char answer[WORD_LEN][WORD_LEN], char game[WORD_LEN][WORD_LEN]){
    int i, j;
    for (i = 0; i < WORD_LEN; i++){
        for (j = 0; j < WORD_LEN; j++){
            answer[i][j] = '.';
            game[i][j] = '#';
        }
    }
}

// reads in words from either stdin or file depending on number of command line arguments
int getWords(Word wordList[NUM_WORDS], int c, char fname[]){
    char line[100];
    int count = 0;

    // file handling
    FILE *f;
    if (c == 2){
        f = fopen(fname, "r");
        if (!f){
            printf("ERROR: Invalid file name.\n");
            return -1;
        }
    }

    // reading each line from the file or user
    while (line[0] != '.' && count < NUM_WORDS){
        switch (c){
            case 1:
                printf("Enter a word (%d remaining): ", NUM_WORDS - count);
                fgets(line, 101, stdin);
                break;
            case 2:
                fgets(line, 101, f);
                break;
        }
        line[strlen(line)-1] = '\0';

        // make sure the first entry is not '.'
        if (line[0] == '.' && count == 0){
            printf("ERROR: Please enter a word before creating the crossword.\n");
            line[0] = '\0';
        }
        else {
            // check if a word is legitimate and if so, make it uppercase and add it to the word list
            if (processWord(line)) {
                strcpy(wordList[count].word, line);
                wordList[count].inPuzzle = 0;
                count++;
            }
            else if (line[0] != '.') printf("Invalid word ignored: %s\n", line);
        }
    }
    // remove '.' from last word list entry
    if (count <= NUM_WORDS){
        strcpy(wordList[count].word, "\0");
    }
    if (c == 2){
        fclose(f);
    }
    return count;
}

// checks if a word is legitimate, returning 1 if it is and 0 if it isn't
int processWord(char word[100]){
    int i;
    int len = strlen(word);
    // checks length
    if (len < 2 || len > WORD_LEN) return 0;
    // checks for letterhood
    for (i = 0; i < len; i++){
        int j = isalpha(word[i]);
        if (!j && word[i] != '\0') return 0;
        else word[i] = toupper(word[i]);
    }
    return 1;
}

// sorts the array of Words into descending by word length using a bubble sort mechanism
void sortWords(Word words[NUM_WORDS], int n){
    Word temp;
    int i, j;
    for (j = 0; j < n - 1; j++){
        for (i = 0; i < n - j - 1; i++){
            if (strlen(words[i].word) < strlen(words[i + 1].word)){
                temp = words[i];
                words[i] = words[i + 1];
                words[i + 1] = temp;
            }
        }
    }
}

// sorts the array of Words into ascending by x value to order the clues for printing using a bubble sort mechanism very similar to the sortWords function
void sortClues(Word words[NUM_WORDS], int n){
    Word temp;
    int i,j;
    for (j = 0; j < n - 1; j++){
        for (i = 0; i < n - j - 1; i++){
            if (words[i].loc[1] > words[i + 1].loc[1]){
                temp = words[i];
                words[i] = words[i + 1];
                words[i + 1] = temp;
            }
        }
    }
}

// main function for placing the words in a crossword properly
void generate(char board[WORD_LEN][WORD_LEN], Word words[NUM_WORDS], int s){
    int i, j;
    int numIn = 1;
    int change = 1;
    int loc[4];

    // placing the first word and assigning its various properties
    words[0].orient = 1;
    words[0].inPuzzle = 1;
    words[0].loc[0] = WORD_LEN / 2;
    words[0].loc[1] = (WORD_LEN / 2) - (strlen(words[0].word) / 2);
    for (i = 0; i < strlen(words[0].word); i++) {
        board[words[0].loc[0]][words[0].loc[1] + i] = words[0].word[i];
    }

    // placing the rest of the words, this loop is repeated until no more words are added to the puzzle on an iteration over the word list
    while (numIn){
        numIn = 0;

        // iterating through each unplaced word in the word list
        for (i = 1; i < s; i++){
            if (words[i].inPuzzle == 0){

                // finding location for word and setting orientation
                locateWord(board, words[i], loc);
                words[i].orient = loc[3];
                int n = 0;

                // placing a word across
                if (words[i].orient == 1){
                    words[i].inPuzzle = 1;
                    words[i].loc[0] = loc[0];
                    words[i].loc[1] = loc[1] - loc[2];
                    numIn++;
                    for (j = loc[1] - loc[2]; j < loc[1] - loc[2] + strlen(words[i].word); j++){
                        board[loc[0]][j] = words[i].word[n];
                        n++;
                    }
                }

                // placing a word down
                else if (words[i].orient == 2){
                    words[i].inPuzzle = 1;
                    words[i].loc[0] = loc[0] - loc[2];
                    words[i].loc[1] = loc[1];
                    numIn++;
                    for (j = loc[0] - loc[2]; j < loc[0] - loc[2] + strlen(words[i].word); j++){
                        board[j][loc[1]] = words[i].word[n];
                        n++;
                    }
                }
            }
        }
    }

    // printing out all of the words that could not fit
    for (i = 0; i < s; i++){
        if (words[i].inPuzzle == 0) printf("Skipped word: %s\n", words[i].word);
    }
}

// sets word location characteristics in loc array, with loc[3] being 0 if there is no place for the word
int locateWord(char board[WORD_LEN][WORD_LEN], Word w, int loc[4]){
    // iterating through each letter of the word being placed and each character of the answer board
    int i, j, k;
    for (i = 0; i < strlen(w.word); i++){
        for (j = 0; j < WORD_LEN; j++){
            for (k = 0; k < WORD_LEN; k++){
                // confirming letters match before proceeding
                if (board[j][k] == w.word[i]){
                    // setting loc[3] to the orientation of a potential spot
                    loc[3] = neighbors(board, j, k);

                    // setting other location properties if the word fits in the current spot and the orientation value is right
                    if (loc[3] != 0 && wordFit(board, w, j, k, i, loc[3])){
                        loc[0] = j;
                        loc[1] = k;
                        loc[2] = i;
                        return 1;
                    }
                    else loc[3] = 0;
                }
            }
        }
    }
    return 0;
}

// checking an intersection spot to see if a word can be placed across or down at it
int neighbors(char board[WORD_LEN][WORD_LEN], int x, int y){
    // conditional mins and maxes to account for edge cases
    int xmin = x == 0 ? 0 : x - 1;
    int ymin = y == 0 ? 0 : y - 1;
    int xmax = x == WORD_LEN - 1 ? WORD_LEN : x + 2;
    int ymax = y == WORD_LEN - 1 ? WORD_LEN : y + 2;

    // checking corners of intersection spot
    if (board[x][y] != '.' && (board[xmin][ymin] == '.' && board[xmin][ymax - 1] == '.' && board[xmax - 1][ymin] == '.' && board[xmax - 1][ymax - 1] == '.')){
        // checking adjacent cells and determining across or down
        if ((board[xmin][y] != '.' || board[xmax - 1][y] != '.') && (board[x][ymin] == '.' && board[x][ymax-1] == '.')) return 1;
        else if ((board[x][ymin] != '.' || board[x][ymax-1] != '.') && (board[xmin][y] == '.' && board[xmax - 1][y] == '.')) return 2;
    }
    // returning 0 if the spot is invalid
    return 0;
}

// checking a word at an intersection spot to see if it would fit into the space on the current board
int wordFit(char board[WORD_LEN][WORD_LEN], Word w, int x, int y, int z, int o){
    int i, j, start, end;

    // checking for a word across
    if (o == 1){
        start = y - z;
        end = y - z + strlen(w.word);

        // iterating one space more than the length of the word on either end and checking for each cell to be empty and their adjacent cells to be empty
        for (j = start - 1; j < end + 1; j++){
            if (j == y);
            else if (board[x][j] != '.') return 0;
            else if ((board[x+1][j] != '.' || board[x-1][j] != '.') && j != start - 1 && j != end) return 0;
        }
    }

    // checking for a word down
    else if (o == 2){
        start = x - z;
        end = x - z + strlen(w.word);
        for (j = start - 1; j < end + 1; j++){
            if (j == x);
            else if (board[j][y] != '.') return 0;
            else if ((board[j][y+1] != '.' || board[j][y-1] != '.') && j != start - 1 && j != end) return 0;
        }
    }
    else return 0;
    // checking if the word goes off the edge
    if (end > WORD_LEN || start < 0) return 0;
    return 1;
}

// setting the blanks on the puzzle board to be consistent with the answer board provided
void setPuzzle(char puzzle[WORD_LEN][WORD_LEN], char answers[WORD_LEN][WORD_LEN]){
    int i, j;
    for (i = 0; i < WORD_LEN; i++){
        for (j = 0; j < WORD_LEN; j++){
            if (answers[i][j] != '.'){
                puzzle[i][j] = ' ';
            }
        }
    }
}

// making the clue/anagram for each word
void makeClues(Word w[NUM_WORDS], int n){
    int i;
    for (i = 0; i < n; i++){
        strcpy(w[i].clue, strfry(w[i].word));
        // strcpy(w[i].clue, w[i].word);
    }
}

// printing the board either to stdout or a file depending on number of command line arguments
void printBoard(char board[WORD_LEN][WORD_LEN], int o, FILE *f){
    int i, j;
    // if file pointer is NULL, i.e. no third argument was found, print to console
    if (!f){
        for (i = -1; i < WORD_LEN + 1; i++){
            for (j = -1; j < WORD_LEN + 1; j++){
                if ((i == -1 || i == WORD_LEN) && j == WORD_LEN) printf("-");
                else if (i == -1 || i == WORD_LEN) printf("--");
                else if (j == -1 || j == WORD_LEN) printf("| ");
                else printf("%c ", board[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    // otherwise print to the pile passed into the function
    else {
        for (i = -1; i < WORD_LEN + 1; i++){
            for (j = -1; j < WORD_LEN + 1; j++){
                if ((i == -1 || i == WORD_LEN) && j == WORD_LEN) fprintf(f, "-");
                else if (i == -1 || i == WORD_LEN) fprintf(f, "--");
                else if (j == -1 || j == WORD_LEN) fprintf(f, "| ");
                else fprintf(f, "%c ", board[i][j]);
            }
            fprintf(f, "\n");
        }
        fprintf(f, "\n");
    }
}

// prints the grid of clues either to stdout or a file depending on number of command line arguments
void printClues(Word w[NUM_WORDS], int n, int o, FILE *f){
    int i, j;
    // if file pointer is NULL, i.e. no third argument was found, print to console
    if (!f){
        printf("Clues:\n\n  X |  Y | ORIENT | CLUE\n");
        for (i = 0; i < WORD_LEN + 20; i++) printf("-");
        printf("\n");
        for (i = 0; i < n; i++){
            if (w[i].inPuzzle != 0){
                char temp[7];
                if (w[i].orient == 1) strcpy(temp, "Across");
                else strcpy(temp, "Down");
                printf(" %2d | %2d | %6s | %s\n", w[i].loc[1], w[i].loc[0], temp, w[i].clue);
            }
        }
        printf("\n");
    }
    // otherwise print to the pile passed into the function
    else {
        fprintf(f, "Clues:\n\n  X |  Y | ORIENT | CLUE\n");
        for (i = 0; i < WORD_LEN + 20; i++) fprintf(f, "-");
        fprintf(f, "\n");
        for (i = 0; i < n; i++) {
            if (w[i].inPuzzle != 0) {
                char temp[7];
                if (w[i].orient == 1)
                    strcpy(temp, "Across");
                else
                    strcpy(temp, "Down");
                fprintf(f, " %2d | %2d | %6s | %s\n", w[i].loc[1], w[i].loc[0], temp, w[i].clue);
            }
        }
    }
}

// wraps every piece into one function and creates, fills, and outputs the crossword
void output(char answers[WORD_LEN][WORD_LEN], char puzzle[WORD_LEN][WORD_LEN], Word words[NUM_WORDS], int n, int o, char fname[]){
    // generate the solutions and p
    sortWords(words, n);
    generate(answers, words, n);
    setPuzzle(puzzle, answers);
    makeClues(words, n);
    sortClues(words, n);

    // if the output is suppoosed to be sent to a file
    FILE *f = NULL;
    if (o == 3){
        f = fopen(fname, "w");
        fprintf(f, "Solution:\n");
        printBoard(answers, o, f);
        fprintf(f, "Crossword Puzzle:\n");
        printBoard(puzzle, o, f);
        printClues(words, n, o, f);
    }
    // otherwise print everything to stdout
    else {
        printf("\nSolution:\n");
        printBoard(answers, o, f);
        printf("Crossword Puzzle:\n");
        printBoard(puzzle, o, f);
        printClues(words, n, o, f);
    }
}    
