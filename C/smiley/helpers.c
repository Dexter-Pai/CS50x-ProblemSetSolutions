#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    // this is some bs copy and paste code i wrote up lol
    // image[0][2].rgbtBlue = 0xff;
    // image[0][3].rgbtBlue = 0xff;
    // image[0][4].rgbtBlue = 0xff;
    // image[0][5].rgbtBlue = 0xff;
    // image[1][1].rgbtBlue = 0xff;
    // image[1][6].rgbtBlue = 0xff;
    // image[2][0].rgbtBlue = 0xff;
    // image[2][2].rgbtBlue = 0xff;
    // image[2][5].rgbtBlue = 0xff;
    // image[2][7].rgbtBlue = 0xff;
    // image[3][0].rgbtBlue = 0xff;
    // image[3][7].rgbtBlue = 0xff;
    // image[4][0].rgbtBlue = 0xff;
    // image[4][1].rgbtBlue = 0xff;
    // image[4][5].rgbtBlue = 0xff;
    // image[4][7].rgbtBlue = 0xff;
    // image[5][0].rgbtBlue = 0xff;
    // image[5][2].rgbtBlue = 0xff;
    // image[5][3].rgbtBlue = 0xff;
    // image[5][7].rgbtBlue = 0xff;
    // image[6][1].rgbtBlue = 0xff;
    // image[6][6].rgbtBlue = 0xff;
    // image[7][2].rgbtBlue = 0xff;
    // image[7][3].rgbtBlue = 0xff;
    // image[7][4].rgbtBlue = 0xff;
    // image[7][5].rgbtBlue = 0xff;

    // this is how you're supposed to do it!
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if (image[h][w].rgbtRed == 0x00 && image[h][w].rgbtBlue == 0x00 && image[h][w].rgbtGreen == 0x00)
            {
                image[h][w].rgbtRed = 0xff;
                image[h][w].rgbtBlue = 0x73;
                image[h][w].rgbtRed = 0xba;
            }
        }
    }

}
