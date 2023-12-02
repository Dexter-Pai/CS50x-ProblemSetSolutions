#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string answer = get_string ("What's your first name? ");
    string answer2 = get_string ("What's your last name? ");
    printf ("Hello, %s %s\n", answer, answer2);

}