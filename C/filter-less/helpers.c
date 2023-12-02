#include "helpers.h"
#include <math.h>

float calculate_sepia(float c, BYTE a);

int check_upperBoundry(int a);

void surroundingBlocks(int h, int w, int height, int width, RGBTRIPLE image[height][width]);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtBlue = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);
            image[h][w].rgbtGreen = image[h][w].rgbtBlue;
            image[h][w].rgbtRed = image[h][w].rgbtBlue;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // calculate_sepia(.393, image[h][w].rgbtRed);
            int sepia_red = round(calculate_sepia(.393, image[h][w].rgbtRed) +
                                  calculate_sepia(.769, image[h][w].rgbtGreen) +
                                  calculate_sepia(.189, image[h][w].rgbtBlue));
            sepia_red = check_upperBoundry(sepia_red);
            int sepia_green = round(calculate_sepia(.349, image[h][w].rgbtRed) +
                                    calculate_sepia(.686, image[h][w].rgbtGreen) +
                                    calculate_sepia(.168, image[h][w].rgbtBlue));
            sepia_green = check_upperBoundry(sepia_green);
            int sepia_blue = round(calculate_sepia(.272, image[h][w].rgbtRed) +
                                   calculate_sepia(.534, image[h][w].rgbtGreen) +
                                   calculate_sepia(.131, image[h][w].rgbtBlue));
            sepia_blue = check_upperBoundry(sepia_blue);
            // int sepia_blue = ((int)(.393 * image[h][w].rgbtRed)) + ((int)(.769 * image[h][w].rgbtGreen)) + ((int)(.189 * image[h][w].rgbtBlue));
            // int sepia_green = ((int)(.349 * image[h][w].rgbtRed)) + ((int)(.686 * image[h][w].rgbtGreen)) + ((int)(.168 * image[h][w].rgbtBlue));
            // int sepia_red = ((int)(.272 * image[h][w].rgbtRed)) + ((int)(.534 * image[h][w].rgbtGreen)) + ((int)(.131 * image[h][w].rgbtBlue));
            image[h][w].rgbtBlue = sepia_blue;
            image[h][w].rgbtGreen = sepia_green;
            image[h][w].rgbtRed = sepia_red;
        }
    }

    return;
}

float calculate_sepia(float c, BYTE a)
{
    float d = a;
    float b = c * d;
    // int tmp = round(b);
    return b;
}

int check_upperBoundry(int a)
{
    if (a >= 255)
    {
        a = 255;
    }

    return a;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int arrayWidth = width - 1;
    for (int h = 0; h < height; h++)
    {
        // if (width % 2 == 0)
        // {
        for (int w = 0; w < width / 2; w++)
        {
            RGBTRIPLE tmp = image[h][arrayWidth - w];
            image[h][arrayWidth - w] = image[h][w];
            image[h][w] = tmp;
        }
        // }
        // else
        // {
        //     for (int w = 0; w < ((arrayWidth / 2) - 1); w++)
        //     {
        //         RGBTRIPLE tmp = image[h][arrayWidth - w];
        //         image[h][arrayWidth - w] = image[h][w];
        //         image[h][w] = tmp;
        //     }
        // }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float tempRed = 0;
    float tempBlue = 0;
    float tempGreen = 0;
    float counter = 0.0;
    RGBTRIPLE newimage[height][width];
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            // surroundingBlocks(h, w, height, width, image[height][width]);
            // surrounding blocks determination
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (h + x < 0 || h + x > height - 1 || w + y < 0 || w + y > width - 1)
                    {
                        //invalid
                    }
                    else
                    {
                        tempRed += image[h + x][w + y].rgbtRed;
                        tempGreen += image[h + x][w + y].rgbtGreen;
                        tempBlue += image[h + x][w + y].rgbtBlue;
                        counter++;
                    }

                }
            }
            newimage[h][w].rgbtRed = round(tempRed / counter);
            newimage[h][w].rgbtGreen = round(tempGreen / counter);
            newimage[h][w].rgbtBlue = round(tempBlue / counter);

            tempRed = 0;
            tempGreen = 0;
            tempBlue = 0;
            counter = 0;
        }
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = newimage[h][w].rgbtRed;
            image[h][w].rgbtBlue = newimage[h][w].rgbtBlue;
            image[h][w].rgbtGreen = newimage[h][w].rgbtGreen;
        }
    }
    return;
}

// void surroundingBlocks(int h, int w, int height, int width, RGBTRIPLE image[height][width])
// {
//     for (int i = -1; i < 2; i++)
//     {
//         for (int j = -1; j < 2; j++)
//         {
//             if (h + i >= 0 && h + i <= height - 1 && w + j >= 0 && w + j <= width - 1)
//             {

//             }
//         }
//     }
// }