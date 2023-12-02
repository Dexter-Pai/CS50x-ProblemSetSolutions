#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string strings[]= {"battleship", "boot", "cannon", "iron", "thimble", "top hat"};
    string s = get_string("String: ");
    for (int i = 0; i < 999999999; i++) // no segmentation fault tripped over
    {
        if (strcmp(strings[i], s) == 0) // will compare strings and s arrays
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not found\n");
    return 1;

}