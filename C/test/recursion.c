#include <cs50.h>
#include <stdio.h>

void draw(int n); // prototype

int main(void)
{
    int height = get_int("Height : ");
    draw(height);
}

void draw(int n)
{
    if (n <= 0)
    return;
    draw(n - 1);

    for (int j = 0; j < n; j++)
    {
        printf("#");
    }
    printf("\n");
    // draw(n + 1); this method will create problems
    // if(n + 1 == 3)
    // {
    //     break;
    // }
}