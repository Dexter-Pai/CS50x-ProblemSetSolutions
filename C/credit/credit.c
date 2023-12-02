#include <cs50.h>
#include <stdio.h>

void checkCreditCard(void);
long getInput(void);
int lengthDetermination(long n);
bool isItCorrectLength(int n);
bool validCard(long n);

int main(void)
{
    // while (true)//debug
    // {
    checkCreditCard();
    // }
}

void checkCreditCard(void)
{
    long num = getInput();
    const int i = lengthDetermination(num);
    if (isItCorrectLength(i))
    {
        //is it according to Luhn's law
        if (validCard(num))
        {
            //3 num / 10, 4 num / 100, 5 num / 1000
            for (int j = 0; j < (i - 2); j++)
            {
                num /= 10;
            }
            if (num == 37 && i == 15)
            {
                printf("AMEX\n");
            }
            else if (num == 30 && i == 14)
            {
                printf("DINNER\n");
            }
            else if (((num == 40 || num == 41 || num == 49) && i == 16) || (num == 42 && i == 13))
            {
                printf("VISA\n");
            }
            else if ((num == 22 || num == 55 || num == 51 || num == 52) && i == 16)
            {
                printf("MASTERCARD\n");
            }
            else if (num == 35 && i == 16)
            {
                printf("JCV\n");
            }
            else if (num == 60 && i == 16)
            {
                printf("DISCOVER\n");
            }
            else
            {
                printf("INVALID\n");
            }

        }
        else
        {
            printf("INVALID\n");
        }

        //does it start with 37amex, 30dinner, 60discover, 35jcv, 22 55 51 52master, 40 41 42 49 visa
    }
    else
    {
        //invalid
        printf("INVALID\n");
    }
}

long getInput(void)
{
    long i;
    do
    {
        i = get_long("input: ");
    }
    while (i < 0);
    return i;
}

int lengthDetermination(long n)
{
    int i = 0;
    while (n > 0)
    {
        n /= 10;
        i++;
    }
    return i;
}

bool isItCorrectLength(int n)
{
    if (n >= 13 && n <= 16)
    {
        return true;
    }
    return false;
}

bool validCard(long n) // still wrong
{
    // return true;
    // not not doubled added
    long nda = 0;
    long da = 0;
    int i = 1;
    // printf("this is n : %li\n", n); debug
    while (n > 0)
    {

        if (i % 2 == 0)
        {
            int tmp = 0; // to check if the doubled value is more than 10
            tmp = (n % 10) * 2;
            if (tmp >= 10)//> or >=?
            {
                int tmp2 = 0;
                while (tmp > 0)
                {
                    tmp2 += tmp % 10;
                    tmp /= 10;
                }
                da += tmp2;
            }
            else
            {
                da += (n % 10) * 2;
            }
            n /= 10;
            i++;
        }
        else
        {
            nda += n % 10;
            n /= 10;
            i++;
        }
        // when total length is divisible by 2,
        //while length is 3, do it 3 times, first iteration i=0 always goes to nda;
        //135, divide by 10, 130, module goes to nda;
        //divide by 10 13, modulo x 2 goes to da;
        //modulo 10 1 , modulo goes to nda;
    }

    long tmp = (nda + da);
    // printf("this is result : %li\n",tmp); debug

    if ((nda + da) % 10 == 0)
    {
        return true;
    }
    return false;
}

//3 num / 10, 4 num / 100, 5 num / 1000











// int isItValidLength(int n)
// {
//     while (n > 0)
// }

/*
input use get long///

f is it a credit card? 13, 16 visa , 16 master, amex 15, dinner 14, discover 16, jcb 16
length determination///
is it correct number length? if length valid, check other values





*/