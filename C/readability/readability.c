#include <cs50.h>
#include <stdio.h>
#include <string.h>

int L;
int W;
int S;

void letters(string s);
float average(int arg1);

int main(void)
{
    // while(true){
    string input = get_string("Input your text here : ");
    letters(input);

    // printf("%i %i %i\n",L,W,S);
    //                    29 / 3 * 100  56.84          4 / 8 * 100 14.8
    float index = (0.0588 * average(L)) - (0.296 * average(S)) - 15.8;
    int tmp = (int) index;
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if ((int)(index + 0.5) > tmp)
    {
        tmp = (int) index + 1;
        // if (tmp > 16)
        printf("Grade %i\n", tmp);
    }
    else if (tmp > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", tmp);
    }
    // printf("%i\n%i\n%i\n",L,W,S);
    // }
}

void letters(string s)
{
    // if a-z,
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
        {
            L++;
        }
        if (s[i] == ' ')
        {
            W++;
        }
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            S++;
        }
    }
    W++;
}

float average(int arg1)
{
    return ((float) arg1 * 100 / (float) W);
}