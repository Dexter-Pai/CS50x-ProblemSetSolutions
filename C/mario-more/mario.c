#include <cs50.h>
#include <stdio.h>

void printObstacle(int arg1);

int main(void)
{
    int h;
    do
    {
        h = get_int("Input height: ");
    }
    while (h < 1 || h > 8);
    //prompt height 1-8, use# to build
    //each row has 2 gaps
    printObstacle(h);

}
//white space calculation if height 1, 0, if hight 2, 1,0 height 3, 2,1,0
void printObstacle(int arg1)
{
    int arg2 = arg1;
    while (arg1 > 0)
    {
        int j = 0;
        for (int i = 0; i < (arg1 - 1); i++)
        {
            printf(" ");
            j++;
        }
        //print n# arg1-j+1
        for (int i = 0; i < (arg2 - j); i++)
        {
            printf("#");
        }
        //print gap
        printf("  ");
        //print n#
        for (int i = 0; i < (arg2 - j); i++)
        {
            printf("#");
        }
        //print \n
        printf("\n");
        arg1--;
    }
}


