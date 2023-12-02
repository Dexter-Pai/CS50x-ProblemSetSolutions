#include <cs50.h>
#include <stdio.h>


int determineCharacterCountInAFile(FILE *sav);

int main(void)
{
    FILE *sav = fopen("sav.txt", "r");
    int wordCounter = determineCharacterCountInAFile(sav);
    int i = 0;
    fclose(sav);
}

int determineCharacterCountInAFile(FILE *sav)
{
    int counter = 0;
    for (int i = 0; fgetc(sav) != EOF; i++)
    {
        counter++;
    }
    return counter;
}