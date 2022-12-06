// Walker Bagley
// CSE 20311 Lab 5

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET 26
#define ASCII_BEGIN 97

int main(){
    int letters[ALPHABET] = {0};
    char l;
    int count = 0, let = 0;
    char file[30];
    FILE *f;
    printf("Enter the name of the text file: ");
    scanf("%s", file);
    f = fopen(file, "r");
    if (!f) {
        printf("ERROR: File %s not found\n", file);
        return 1;
    }

    while (1){
        fscanf(f, "%c", &l);
        if(feof(f)) break;
        l = tolower(l);
        l -= ASCII_BEGIN;
        if (l >= 0 && l <= ALPHABET){
            letters[l]++;
            let ++;
        }
        count ++;
    }

    printf("\nGeneral summary of %s:\n", file);
    printf("Total characters: %d\n", count);
    printf("Total letters: %d\n", let);
    printf("\nLetter counts:");
    for (int i = 0; i < ALPHABET; i++)
    {
        if (i%6==0) printf("\n");
        printf("   %c: %6d", i + ASCII_BEGIN, letters[i]);
    }
    printf("\n\nLetter percents:");
    for (int i = 0; i < ALPHABET; i++)
    {
        if (i%6==0) printf("\n");
        printf("   %c: %5.1f%%", i + ASCII_BEGIN, (float) 100 * letters[i] / let);
    }
    printf("\n");
    return 0;
}