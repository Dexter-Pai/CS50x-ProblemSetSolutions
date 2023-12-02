#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int startSize;
    int endSize;
    int n = 0;

    // TODO: Prompt for start size
    do
    {
        startSize = get_int("Start population: ");
    }
    while (startSize < 9);

    // TODO: Prompt for end size
    do
    {
        endSize = get_int("End population: ");
    }
    while (endSize < startSize);

    // TODO: Calculate number of years until we reach threshold
    while (startSize < endSize)
    {
        startSize += (startSize / 3) - (startSize / 4);
        n++;
    }

    // TODO: Print number of years
    printf("Number of years required: %i\n", n);
}
