#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //prompting username
    string name = get_string("What's your name: ");
    //printing
    printf("hello, %s\n", name);
}