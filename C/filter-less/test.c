#include <stdio.h>

typedef struct
{
    int  rgbtBlue;
}
RGBTRIPLE;

void surroundingBlock(int h, int w, int height, int width);

int main(void)
{

    RGBTRIPLE image[3][3];

    image[0][0].rgbtBlue= 1;
    image[0][1].rgbtBlue= 2;
    image[0][2].rgbtBlue= 3;
    image[1][0].rgbtBlue= 6;
    image[1][1].rgbtBlue= 7;
    image[1][2].rgbtBlue= 9;
    image[2][0].rgbtBlue= 4;
    image[2][1].rgbtBlue= 5;
    image[2][2].rgbtBlue= 8;

    int height = 3;
    int width = 3;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            surroundingBlock(h, w, height, width);
        }
    }

}

void surroundingBlock(int h, int w, int height, int width)
{

}