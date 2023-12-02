#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (void)
{
    string a = "Hello";
    printf("%i\n",(int)a[0]);
    printf("%i\n",a[0]);
    if (a[0] == 72)
    printf("char can be compared directly with value from ascii\n");
}
