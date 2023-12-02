#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int LENGTH = 0;
char KEY[26];
char LKEY[26];
char CIPHER[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

bool duplicateCheck(void);
bool invalidCharacterCheck(void);
void cipher(string arg1);

int main(int argc, string argv[])
{
    // bool faulty = false;
    if (argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (argc == 2 && strlen(argv[1]) == 26)/// && length == 26
    {
        LENGTH = strlen(argv[1]); // length determine
        for (int i = 0, j = 26; i < j; i++) // check each word for invalid character
        {
            KEY[i] = toupper(argv[1][i]);
            // if ((argv[1][i] >= 'a' && argv[1][i] <= 'z') || (argv[1][i] >= 'A' && argv[1][i] <= 'Z')) //if valid a-z
            // {
            // }
            // else //if invalid
            // {
            //     j = 0;
            //     return 1;
            // }
        }

        // length = strlen(argv[1]);
        // if (int i = 0; i < length; i++)
        // {

        // }
        printf("ok %i\n", LENGTH);
        printf("Your word is: ");
        for (int i = 0; i < strlen(KEY); i++)
        {
            printf("%c", KEY[i]);
        }
        printf("\n");
        if (duplicateCheck())
        {
            printf("There are duplicate\n");
            return 1;
        }
        printf("There are no duplicate\n");

        if (invalidCharacterCheck())
        {
            printf("There are invalid Characters\n");
            return 1;
        }
        printf("There are no invalid Characters\n");

        //prompt
        string input = get_string("Words to chipher: ");
        printf("\n");
        cipher(input); //output to CIPHER global string
        //cipher
        // for (int i = 0; i < LENGTH; i++)
        // {
        //     printf("%s",CIPHER[i]);
        // }
        return 0;
    }
    else
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

}

bool duplicateCheck(void)
{
    int l = strlen(KEY);
    //another for loop
    for (int tmp = 0; tmp < l; tmp++)// every array is checked
    {
        for (int i = tmp + 1, j = l; i < j; i++)// one on the array is equal to another or not
        {
            if (KEY[tmp] == KEY[i])
            {
                return true;
            }
        }
    }
    return false;
}

bool invalidCharacterCheck(void)
{
    int l = strlen(KEY);
    for (int i = 0; i < l; i++)
    {
        if (KEY[i] < 'A' || KEY[i] > 'Z')
        {
            return true;
        }
    }
    return false;
}

void cipher(string arg1)
{
    for (int i = 0; i < 26; i++)
    {
        LKEY[i] = KEY[i] + 32;
        // printf("%c",LKEY[i]);
    }
    int l = strlen(arg1);
    printf("ciphertext: ");
    for (int i = 0; i < l; i++)
    {
        if (arg1[i] >= 65 && arg1[i] <= 90) //uppercase
        {
            printf("%c", KEY[arg1[i] - 65]);
        }
        else if (arg1[i] >= 97 && arg1[i] <= 122) //lowercase
        {
            printf("%c", LKEY[arg1[i] - 97]);
        }
        else
        {
            printf("%c", arg1[i]);
        }
    }
    printf("\n");
}
/*
ascii table 65 to 90 for uppercase
if upper case
for eg HHH
72 - 65 = correct index to look for answer.
array no. 7 value is the correct one.
value (index number 72-65=7)
for eg index 7 has value of P
P print

for lowercase
if lowercase
make lowercase array first
for eg hhh
104 -97 =7correct index to look for answer.
array no. 7 value is the correct one.
value (index number 72-65=7)
for eg index 7 has value of P
P print
*/