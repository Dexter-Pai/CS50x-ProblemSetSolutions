#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
char CHARACTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    int l_CHARACTERS = strlen(CHARACTERS);
    int l = strlen(word);
    int tmp = 0; //tmp counter for checking
    int score = 0;
    char uppercase_word[l];

    //changed to uppercase
    for (int i = 0; i < l; i++)
    {
        uppercase_word[i] = toupper(word[i]);
    }

    while (tmp < l)
    {
        if (uppercase_word[tmp] >= 'A' && uppercase_word[tmp] <= 'Z')
        {
            for (int i = 0; i < l_CHARACTERS; i++)
            {
                if (uppercase_word[tmp] == CHARACTERS[i])
                {
                    score += POINTS[i];
                }
            }
            tmp++;
        }
        else
        {
            tmp++;
        }
    }
    printf("%i\n", score);
    return score;
}
