#include <stdio.h>
  
int main () 
{
    int touchdowns = 0;
    int extraPoints = 0;
    int fieldGoals = 0;
    int safeties = 0;
    printf("Touchdowns: ");
    scanf("%d", &touchdowns);
    printf("Extra Points: ");
    scanf("%d", &extraPoints);
    printf("Field Goals: ");
    scanf("%d", &fieldGoals);
    printf("Safeties: ");
    scanf("%d", &safeties);

    printf("Points: %d\n",touchdowns*6+extraPoints+fieldGoals*3+safeties*2);

    return 0;
}