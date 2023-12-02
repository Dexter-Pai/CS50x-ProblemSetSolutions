#include <stdio.h>

int main(void)
{
    // int x = get_int
    int x;
    printf("x: ");
    scanf("%i", &x); // expected int, therefore %i; if you use x directly, it cannot change the values
                     // use &x to change
                     // if the user doesn't input the type int value, you need to reprompt manually
    printf("x: %i\n", x);
}