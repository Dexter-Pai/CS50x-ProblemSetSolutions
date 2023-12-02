#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string s = get_string("your input :");
    for (int i = 0, length = strlen(s); i < length; i++)
        printf("%c", toupper(s[i]));
    printf("\n");
}