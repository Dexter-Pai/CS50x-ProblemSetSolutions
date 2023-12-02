#include <cs50.h>
#include <stdio.h>

int main (void)
{
    int i = 0;
    while (i!=1)
    {
        char c = get_char("Do you agree? ");
        if (c == 'y' || c == 'Y')
        {
            printf("Agreed.\n");
            i = 1;
        }
        else if (c == 'n' || c == 'N')
        {
            printf("Not agreed.\n");
            i = 1;
        }
        else
        {
            printf("You have entered in invalid character.\n");
        }
    }



}