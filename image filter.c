#include "helpers.h"
#include <math.h>

//
int getResult(int a)
{
    if(a > 255)
    {
        return 255;
    }
    else
    {
        return a;
    }
}
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            int tmp = round((image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.0);
            image[h][w].rgbtRed = tmp;
            image[h][w].rgbtGreen = tmp;
            image[h][w].rgbtBlue = tmp;
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
            int tmpRed = getResult(round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue));
            int tmpGreen = getResult(round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue));
            int tmpBlue = getResult(round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue));
            image[h][w].rgbtRed = tmpRed;
            image[h][w].rgbtGreen = tmpGreen;
            image[h][w].rgbtBlue = tmpBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)

    {
        for (int w = 0, i = 1; w < width / 2; w++)
        {
            int left_to_right = 0;
            int right_to_left = 0;

            //For RED
            left_to_right = image[h][w].rgbtRed;
            right_to_left = image[h][width - i].rgbtRed;

            image[h][w].rgbtRed = right_to_left;
            image[h][width - i].rgbtRed = left_to_right;

            //For GREEN
            left_to_right = image[h][w].rgbtGreen;
            right_to_left = image[h][width - i].rgbtGreen;

            image[h][w].rgbtGreen = right_to_left;
            image[h][width - i].rgbtGreen = left_to_right;

            //For BLUE
            left_to_right = image[h][w].rgbtBlue;
            right_to_left = image[h][width - i].rgbtBlue;

            image[h][w].rgbtBlue = right_to_left;
            image[h][width - i].rgbtBlue = left_to_right;

            i++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int new_h = height + 2, new_w = width + 2;
    RGBTRIPLE old[new_h][new_w];

    for (int h = 0; h < new_h; h++)
    {
        for (int w = 0; w < new_w; w++)
        {

            old[h][w].rgbtRed = 0;
            old[h][w].rgbtGreen = 0;
            old[h][w].rgbtBlue = 0;
        }
    }

    for (int h = 1, t = 0; h < new_h - 1; h++)
    {
        for (int w = 1, l = 0; w < new_w - 1; w++)
        {
            old[h][w] = image[t][l];

            l++;
        }
        t++;
    }


    for (int h = 1; h < new_h - 1; h++)
    {
        for (int w = 1; w < new_w - 1; w++)
        {
            double total = 9.0;
            if ((h == 1 && w > 1) || (h > 1 && w == 1) || ((h == new_h - 2) && w > 1) || (h > 1 && (w == new_w - 2)))
            {
                total = 6.0;
            }

            if ((h == 1 && w == 1) || (h == (new_h - 2) && w == 1) || (h == 1 && w == (new_w - 2)) || (h == (new_h - 2) && w == (new_w - 2)))
            {
                total = 4.0;
            }

            image[h - 1][w - 1].rgbtRed = round((old[h - 1][w - 1].rgbtRed +
                                                 old[h - 1][w].rgbtRed +
                                                 old[h - 1][w + 1].rgbtRed +
                                                 old[h][w - 1].rgbtRed +
                                                 old[h][w].rgbtRed +
                                                 old[h][w + 1].rgbtRed +
                                                 old[h + 1][w - 1].rgbtRed +
                                                 old[h + 1][w].rgbtRed +
                                                 old[h + 1][w + 1].rgbtRed) / total);

            image[h - 1][w - 1].rgbtBlue = round((old[h - 1][w - 1].rgbtBlue +
                                                  old[h - 1][w].rgbtBlue +
                                                  old[h - 1][w + 1].rgbtBlue +
                                                  old[h][w - 1].rgbtBlue +
                                                  old[h][w].rgbtBlue +
                                                  old[h][w + 1].rgbtBlue +
                                                  old[h + 1][w - 1].rgbtBlue +
                                                  old[h + 1][w].rgbtBlue +
                                                  old[h + 1][w + 1].rgbtBlue) / total);

            image[h - 1][w - 1].rgbtGreen = round((old[h - 1][w - 1].rgbtGreen +
                                                   old[h - 1][w].rgbtGreen +
                                                   old[h - 1][w + 1].rgbtGreen +
                                                   old[h][w - 1].rgbtGreen +
                                                   old[h][w].rgbtGreen +
                                                   old[h][w + 1].rgbtGreen +
                                                   old[h + 1][w - 1].rgbtGreen +
                                                   old[h + 1][w].rgbtGreen +
                                                   old[h + 1][w + 1].rgbtGreen) / total);
        }
    }
    return;
}
