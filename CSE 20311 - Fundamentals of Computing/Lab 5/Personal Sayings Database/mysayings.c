// Walker Bagley
// CSE 20311 Lab 5

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SAY_LEN 256

void printMenu();
void printSayings(char[][SAY_LEN], int);
void enterSaying(char[][SAY_LEN], int*);
void sayingsWithWord(char[][SAY_LEN], int);
void numOfSayings(int);
void longestSaying(char[][SAY_LEN], int);
void shortestSaying(char[][SAY_LEN], int);
void saveToFile(char[][SAY_LEN], int);

int main(){
    // setup and file reading
    int run = 1;
    char file[30];
    FILE *f;
    printf("Enter the name of the text file: ");
    fgets(file, 30, stdin);
    file[strcspn(file, "\n")] = 0;
    f = fopen(file, "r");

    // checking for file existence
    if (!f) {
        printf("ERROR: File %s not found\n", file);
        return 1;
    }

    // reading sayings into the local array
    int count = 0;
    char sayings[50][SAY_LEN];
    while (1)
    {
        fgets(sayings[count], SAY_LEN, f);
        sayings[count][strcspn(sayings[count], "\n")] = 0;
        if(feof(f)) break;
        count ++;
    }

    // running the program with a switch
    while (run){
        printMenu();
        char c[5];
        fgets(c, 5, stdin);
        int n = atoi(c);
        switch (n){
            case 1:
                printSayings(sayings, count);
                break;
            case 2:
                enterSaying(sayings, &count);
                break;
            case 3:
                sayingsWithWord(sayings, count);
                break;
            case 4:
                numOfSayings(count);
                break;
            case 5:
                longestSaying(sayings, count);
                break;
            case 6:
                shortestSaying(sayings, count);
                break;
            case 7:
                saveToFile(sayings, count);
                break;
            case 8:
                run = 0;
                fclose(f);
                break;
            default:
                printf("ERROR: Invalid choice.");
                break;
        }
    }
    return 0;
}

// Prints the menu of choices for this program
void printMenu(){
    printf("\n1 - Display all sayings currently in database\n2 - Enter a new saying into the database\n3 - List sayings that contain a specific word\n4 - Print number of sayings in database\n5 - Find the longest saying in the database\n6 - Find the shortest saying in the database\n7 - Save all sayings in a new text file\n8 - Quit the program\nEnter your choice: ");
}

// Prints each saying stored in the argument array as a bulletted list
void printSayings(char sayings[][SAY_LEN], int s){
    printf("\n");
    int i;
    for (i = 0; i < s; i++)
    {
        printf(" - %s\n", sayings[i]);
    }
}

// This is broken atm
void enterSaying(char sayings[][SAY_LEN], int *s){
    printf("Enter a saying: ");
    fgets(sayings[*s], SAY_LEN, stdin);
    sayings[*s][strcspn(sayings[*s], "\n")] = 0;
    ++*s;
}

// Prompts user for a word and then checks each string in the argument array for that word and prints the strings that contain it
void sayingsWithWord(char sayings[][SAY_LEN], int s){
    char word[20];
    printf("Enter word to check: ");
    fgets(word, 20, stdin);
    word[strcspn(word, "\n")] = 0;
    printf("\nSayings that contain %s:\n", word);
    int i;
    for (i = 0; i < s; i++){
        if (strstr(sayings[i], word)){
            printf(" - %s\n", sayings[i]);
        }
    }
}

// Prints number of sayings currently in the database
void numOfSayings(int s){
    printf("\nYou currently have %d sayings.\n", s);
}

// Prints the longest saying in the current database
void longestSaying(char sayings[][SAY_LEN], int s){
    int l = 0;
    int index;
    int i;
    for (i = 0; i < s; i++){
        if (strlen(sayings[i]) > l){
            l = strlen(sayings[i]);
            index = i;
        }
    }
    printf("\n\"%s\" is the longest saying with %d characters.\n", sayings[index], l);
}

// Prints the shortest saying in the current database
void shortestSaying(char sayings[][SAY_LEN], int s){
    int l = SAY_LEN;
    int index;
    int i;
    for (i = 0; i < s; i++){
        if (strlen(sayings[i]) < l){
            l = strlen(sayings[i]);
            index = i;
        }
    }
    printf("\n\"%s\" is the shortest saying with %d characters.\n", sayings[index], l);
}

// Creates new file with name specified by the user and writes each string stored in the argument array into the file
void saveToFile(char sayings[][SAY_LEN], int s){
    char name[30];
    printf("Enter save name: ");
    fgets(name, 30, stdin);
    name[strcspn(name, "\n")] = 0;
    FILE *f;
    f = fopen(name, "w");
    int i;
    for (i = 0; i < s; i++){
        fputs(sayings[i], f);
        fputs("\n", f);
    }
    fclose(f);
    printf("All strings saved in %s\n", name);
}
