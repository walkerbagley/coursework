// Walker Bagley
// CSE 20311 Lab 8
// crossword.c

#include <stdio.h>
#include <string.h>
#include "cwfunc.h"

int main(int argc, char *argv[]){
    // board initialization
    char answers[WORD_LEN][WORD_LEN], puzzle[WORD_LEN][WORD_LEN];
    boardInit(answers, puzzle);

    // word list initialization
    Word wordList[NUM_WORDS];
    int count = 0;

    // handling number of command line arguments for each mode to get the words
    if (argc == 1){
        count = getWords(wordList, 1, "");
    }
    else if (argc == 2 || argc == 3){
        count = getWords(wordList, 2, argv[1]);
        if (count == -1) return 1;
    }
    else {
        printf("\nERROR: too many command line inputs\n");
        return 2;
    }
    
    // run everything and output corresponding crossword
    output(answers, puzzle, wordList, count, argc, argv[2]);
    return 0;
}