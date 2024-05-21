#include "helpers.h"
#include <math.h>
#include <stdio.h>
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
    // RGBTRIPLE old[height][width];
    // for (int h = 0; h < height; h++)
    // {
    //     for (int w = 0; w < width; w++)
    //     {
    //         old[h][w].rgbtRed = image[h][w].rgbtRed;
    //         old[h][w].rgbtGreen = image[h][w].rgbtGreen;
    //         old[h][w].rgbtBlue = image[h][w].rgbtBlue;
    //     }
    // }
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

            //     // For top left corner
            //     image[h - 1][w - 1].rgbtRed = round((old[h - 1][w - 1].rgbtRed +
            //                                          old[h - 1][w].rgbtRed +
            //                                          old[h][w - 1].rgbtRed +
            //                                          old[h][w].rgbtRed) / 4.0);

            //     image[h - 1][w - 1].rgbtGreen = round((old[h - 1][w - 1].rgbtGreen +
            //                                           old[h - 1][w].rgbtGreen +
            //                                           old[h][w - 1].rgbtGreen +
            //                                           old[h][w].rgbtGreen) / 4.0);

            //     image[h - 1][w - 1].rgbtBlue = round((old[h - 1][w - 1].rgbtBlue +
            //                                           old[h - 1][w].rgbtBlue +
            //                                           old[h][w - 1].rgbtBlue +
            //                                           old[h][w].rgbtBlue) / 4.0);

            //     // For top right corner
            //     image[h - 1][w + 1].rgbtRed = round((old[h - 1][w + 1].rgbtRed +
            //                                          old[h - 1][w].rgbtRed +
            //                                          old[h][w + 1].rgbtRed +
            //                                          old[h][w].rgbtRed) / 4.0);

            //     image[h - 1][w + 1].rgbtGreen = round((old[h - 1][w + 1].rgbtGreen +
            //                                           old[h - 1][w].rgbtGreen +
            //                                           old[h][w + 1].rgbtGreen +
            //                                           old[h][w].rgbtGreen) / 4.0);

            //     image[h - 1][w + 1].rgbtBlue = round((old[h - 1][w + 1].rgbtBlue +
            //                                           old[h - 1][w].rgbtBlue +
            //                                           old[h][w + 1].rgbtBlue +
            //                                           old[h][w].rgbtBlue) / 4.0);

            //     // For bottom right corner
            //     image[h + 1][w + 1].rgbtRed = round((old[h + 1][w + 1].rgbtRed +
            //                                          old[h + 1][w].rgbtRed +
            //                                          old[h][w + 1].rgbtRed +
            //                                          old[h][w].rgbtRed) / 4.0);

            //     image[h + 1][w + 1].rgbtGreen = round((old[h + 1][w + 1].rgbtGreen +
            //                                           old[h + 1][w].rgbtGreen +
            //                                           old[h][w + 1].rgbtGreen +
            //                                           old[h][w].rgbtGreen) / 4.0);

            //     image[h + 1][w + 1].rgbtBlue = round((old[h + 1][w + 1].rgbtBlue +
            //                                           old[h + 1][w].rgbtBlue +
            //                                           old[h][w + 1].rgbtBlue +
            //                                           old[h][w].rgbtBlue) / 4.0);

            //     // For bottom left corner
            //     image[h + 1][w - 1].rgbtRed = round((old[h + 1][w - 1].rgbtRed +
            //                                          old[h + 1][w].rgbtRed +
            //                                          old[h][w - 1].rgbtRed +
            //                                          old[h][w].rgbtRed) / 4.0);

            //     image[h + 1][w - 1].rgbtGreen = round((old[h + 1][w - 1].rgbtGreen +
            //                                           old[h + 1][w].rgbtGreen +
            //                                           old[h][w - 1].rgbtGreen +
            //                                           old[h][w].rgbtGreen) / 4.0);

            //     image[h + 1][w - 1].rgbtBlue = round((old[h + 1][w - 1].rgbtBlue +
            //                                           old[h + 1][w].rgbtBlue +
            //                                           old[h][w - 1].rgbtBlue +
            //                                           old[h][w].rgbtBlue) / 4.0);

            //     //For Edges
            //     //top
            //     image[h - 1][w].rgbtRed = round((old[h - 1][w + 1].rgbtRed +
            //                                      old[h - 1][w].rgbtRed +
            //                                      old[h][w + 1].rgbtRed +
            //                                      old[h][w].rgbtRed +
            //                                      old[h][w - 1].rgbtRed +
            //                                      old[h - 1][w - 1].rgbtRed) / 6.0);

            //     image[h - 1][w].rgbtGreen = round((old[h - 1][w + 1].rgbtGreen +
            //                                       old[h - 1][w].rgbtGreen +
            //                                       old[h][w + 1].rgbtGreen +
            //                                       old[h][w].rgbtGreen +
            //                                       old[h][w - 1].rgbtGreen +
            //                                       old[h - 1][w - 1].rgbtGreen) / 6.0);

            //     image[h - 1][w].rgbtBlue = round((old[h - 1][w + 1].rgbtBlue +
            //                                       old[h - 1][w].rgbtBlue +
            //                                       old[h][w + 1].rgbtBlue +
            //                                       old[h][w].rgbtBlue +
            //                                       old[h][w - 1].rgbtBlue +
            //                                       old[h - 1][w - 1].rgbtBlue) / 6.0);

            //     //left
            //     image[h][w - 1].rgbtRed = round((old[h + 1][w - 1].rgbtRed +
            //                                      old[h - 1][w].rgbtRed +
            //                                      old[h + 1][w].rgbtRed +
            //                                      old[h][w].rgbtRed +
            //                                      old[h][w - 1].rgbtRed +
            //                                      old[h - 1][w - 1].rgbtRed) / 6.0);

            //     image[h][w - 1].rgbtGreen = round((old[h + 1][w - 1].rgbtGreen +
            //                                       old[h - 1][w].rgbtGreen +
            //                                       old[h + 1][w].rgbtGreen +
            //                                       old[h][w].rgbtGreen +
            //                                       old[h][w - 1].rgbtGreen +
            //                                       old[h - 1][w - 1].rgbtGreen) / 6.0);

            //     image[h][w - 1].rgbtBlue = round((old[h + 1][w - 1].rgbtBlue +
            //                                       old[h - 1][w].rgbtBlue +
            //                                       old[h + 1][w].rgbtBlue +
            //                                       old[h][w].rgbtBlue +
            //                                       old[h][w - 1].rgbtBlue +
            //                                       old[h - 1][w - 1].rgbtBlue) / 6.0);

            //     //Bottom
            //     image[h + 1][w].rgbtRed = round((old[h + 1][w - 1].rgbtRed +
            //                                      old[h + 1][w].rgbtRed +
            //                                      old[h][w - 1].rgbtRed +
            //                                      old[h][w].rgbtRed +
            //                                      old[h][w + 1].rgbtRed +
            //                                      old[h + 1][w + 1].rgbtRed) / 6.0);

            //     image[h + 1][w].rgbtGreen = round((old[h + 1][w - 1].rgbtGreen +
            //                                       old[h + 1][w].rgbtGreen +
            //                                       old[h][w - 1].rgbtGreen +
            //                                       old[h][w].rgbtGreen +
            //                                       old[h][w + 1].rgbtGreen +
            //                                       old[h + 1][w + 1].rgbtGreen) / 6.0);

            //     image[h + 1][w].rgbtBlue = round((old[h + 1][w - 1].rgbtBlue +
            //                                       old[h + 1][w].rgbtBlue +
            //                                       old[h][w - 1].rgbtBlue +
            //                                       old[h][w].rgbtBlue +
            //                                       old[h][w + 1].rgbtBlue +
            //                                       old[h + 1][w + 1].rgbtBlue) / 6.0);

            //     //Right
            //     image[h][w + 1].rgbtRed = round((old[h + 1][w + 1].rgbtRed +
            //                                      old[h - 1][w].rgbtRed +
            //                                      old[h + 1][w].rgbtRed +
            //                                      old[h][w].rgbtRed +
            //                                      old[h][w + 1].rgbtRed +
            //                                      old[h - 1][w + 1].rgbtRed) / 6.0);

            //     image[h][w + 1].rgbtGreen = round((old[h + 1][w + 1].rgbtGreen +
            //                                       old[h - 1][w].rgbtGreen +
            //                                       old[h + 1][w].rgbtGreen +
            //                                       old[h][w].rgbtGreen +
            //                                       old[h][w + 1].rgbtGreen +
            //                                       old[h - 1][w + 1].rgbtGreen) / 6.0);

            //     image[h][w + 1].rgbtBlue = round((old[h + 1][w + 1].rgbtBlue +
            //                                       old[h - 1][w].rgbtBlue +
            //                                       old[h + 1][w].rgbtBlue +
            //                                       old[h][w].rgbtBlue +
            //                                       old[h][w + 1].rgbtBlue +
            //                                       old[h - 1][w + 1].rgbtBlue) / 6.0);
            //     if ((height % 4) == 0 && (width % 4) == 0)
            //     // if(h > 1  || w > 1)
            //     {

            //         // For top right corner
            //         image[h - 1][w + 1].rgbtRed = round((old[h - 1][w + 1].rgbtRed +
            //                                              old[h - 1][w].rgbtRed +
            //                                              old[h][w + 1].rgbtRed +
            //                                              old[h][w + 2].rgbtRed +
            //                                              old[h - 1][w + 2].rgbtRed +
            //                                              old[h][w].rgbtRed) / 6.0);

            //         image[h - 1][w + 1].rgbtGreen = round((old[h - 1][w + 1].rgbtGreen +
            //                                               old[h - 1][w].rgbtGreen +
            //                                               old[h][w + 1].rgbtGreen +
            //                                               old[h][w + 2].rgbtGreen +
            //                                               old[h - 1][w + 2].rgbtGreen +
            //                                               old[h][w].rgbtGreen) / 6.0);

            //         image[h - 1][w + 1].rgbtBlue = round((old[h - 1][w + 1].rgbtBlue +
            //                                               old[h - 1][w].rgbtBlue +
            //                                               old[h][w + 1].rgbtBlue +
            //                                               old[h][w + 2].rgbtBlue +
            //                                               old[h - 1][w + 2].rgbtBlue +
            //                                               old[h][w].rgbtBlue) / 6.0);

            //         //far most top right
            //         image[h - 1][w + 2].rgbtRed = round((old[h - 1][w + 1].rgbtRed +
            //                                              old[h - 1][w + 2].rgbtRed +
            //                                              old[h][w + 1].rgbtRed +
            //                                              old[h][w + 2].rgbtRed) / 4.0);

            //         image[h - 1][w + 2].rgbtGreen = round((old[h - 1][w + 1].rgbtGreen +
            //                                               old[h - 1][w + 2].rgbtGreen +
            //                                               old[h][w + 1].rgbtGreen +
            //                                               old[h][w + 2].rgbtGreen) / 4.0);

            //         image[h - 1][w + 2].rgbtBlue = round((old[h - 1][w + 1].rgbtBlue +
            //                                               old[h - 1][w + 2].rgbtBlue +
            //                                               old[h][w + 1].rgbtBlue +
            //                                               old[h][w + 2].rgbtBlue) / 4.0);

            //         //Right Old Edge -> Middle
            //         image[h][w + 1].rgbtRed = round((old[h + 1][w + 1].rgbtRed +
            //                                          old[h - 1][w].rgbtRed +
            //                                          old[h + 1][w].rgbtRed +
            //                                          old[h][w].rgbtRed +
            //                                          old[h][w + 1].rgbtRed +
            //                                          old[h][w + 2].rgbtRed +
            //                                          old[h - 1][ w + 2].rgbtRed +
            //                                          old[h + 1][ w + 2].rgbtRed +
            //                                          old[h - 1][w + 1].rgbtRed) / 9.0);

            //         image[h][w + 1].rgbtGreen = round((old[h + 1][w + 1].rgbtGreen +
            //                                           old[h - 1][w].rgbtGreen +
            //                                           old[h + 1][w].rgbtGreen +
            //                                           old[h][w].rgbtGreen +
            //                                           old[h][w + 1].rgbtGreen +
            //                                           old[h][w + 2].rgbtGreen +
            //                                           old[h - 1][ w + 2].rgbtGreen +
            //                                           old[h + 1][ w + 2].rgbtGreen +
            //                                           old[h - 1][w + 1].rgbtGreen) / 9.0);

            //         image[h][w + 1].rgbtBlue = round((old[h + 1][w + 1].rgbtBlue +
            //                                           old[h - 1][w].rgbtBlue +
            //                                           old[h + 1][w].rgbtBlue +
            //                                           old[h][w].rgbtBlue +
            //                                           old[h][w + 1].rgbtBlue +
            //                                           old[h][w + 2].rgbtBlue +
            //                                           old[h - 1][ w + 2].rgbtBlue +
            //                                           old[h + 1][ w + 2].rgbtBlue +
            //                                           old[h - 1][w + 1].rgbtBlue) / 9.0);

            //         // \\ Far Right Edge - New
            //         image[h][w + 2].rgbtRed = round((old[h + 1][w + 1].rgbtRed +
            //                                          old[h][w + 1].rgbtRed +
            //                                          old[h][w + 2].rgbtRed +
            //                                          old[h - 1][ w + 2].rgbtRed +
            //                                          old[h + 1][ w + 2].rgbtRed +
            //                                          old[h - 1][w + 1].rgbtRed) / 6.0);

            //         image[h][w + 2].rgbtGreen = round((old[h + 1][w + 1].rgbtGreen +
            //                                           old[h][w + 1].rgbtGreen +
            //                                           old[h][w + 2].rgbtGreen +
            //                                           old[h - 1][ w + 2].rgbtGreen +
            //                                           old[h + 1][ w + 2].rgbtGreen +
            //                                           old[h - 1][w + 1].rgbtGreen) / 6.0);

            //         image[h][w + 2].rgbtBlue = round((old[h + 1][w + 1].rgbtBlue +
            //                                           old[h][w + 1].rgbtBlue +
            //                                           old[h][w + 2].rgbtBlue +
            //                                           old[h - 1][ w + 2].rgbtBlue +
            //                                           old[h + 1][ w + 2].rgbtBlue +
            //                                           old[h - 1][w + 1].rgbtBlue) / 6.0);

            //         // For bottom left corner - new Edge
            //         image[h + 1][w - 1].rgbtRed = round((old[h + 1][w - 1].rgbtRed +
            //                                              old[h + 1][w].rgbtRed +
            //                                              old[h + 2][w - 1].rgbtRed +
            //                                              old[h + 2][w].rgbtRed +
            //                                              old[h][w - 1].rgbtRed +
            //                                              old[h][w].rgbtRed) / 6.0);

            //         image[h + 1][w - 1].rgbtGreen = round((old[h + 1][w - 1].rgbtGreen +
            //                                               old[h + 1][w].rgbtGreen +
            //                                               old[h + 2][w - 1].rgbtGreen +
            //                                               old[h + 2][w].rgbtGreen +
            //                                               old[h][w - 1].rgbtGreen +
            //                                               old[h][w].rgbtGreen) / 6.0);

            //         image[h + 1][w - 1].rgbtBlue = round((old[h + 1][w - 1].rgbtBlue +
            //                                               old[h + 1][w].rgbtBlue +
            //                                               old[h + 2][w - 1].rgbtBlue +
            //                                               old[h + 2][w].rgbtBlue +
            //                                               old[h][w - 1].rgbtBlue +
            //                                               old[h][w].rgbtBlue) / 6.0);
            //         //Bottom - new Middle
            //         image[h + 1][w].rgbtRed = round((old[h + 1][w - 1].rgbtRed +
            //                                          old[h + 1][w].rgbtRed +
            //                                          old[h + 2][w - 1].rgbtRed +
            //                                          old[h + 2][w].rgbtRed +
            //                                          old[h + 2][w + 1].rgbtRed +
            //                                          old[h][w - 1].rgbtRed +
            //                                          old[h][w].rgbtRed +
            //                                          old[h][w + 1].rgbtRed +
            //                                          old[h + 1][w + 1].rgbtRed) / 9.0);

            //         image[h + 1][w].rgbtGreen = round((old[h + 1][w - 1].rgbtGreen +
            //                                           old[h + 1][w].rgbtGreen +
            //                                           old[h][w - 1].rgbtGreen +
            //                                           old[h + 2][w - 1].rgbtGreen +
            //                                           old[h + 2][w].rgbtGreen +
            //                                           old[h + 2][w + 1].rgbtGreen +
            //                                           old[h][w].rgbtGreen +
            //                                           old[h][w + 1].rgbtGreen +
            //                                           old[h + 1][w + 1].rgbtGreen) / 9.0);

            //         image[h + 1][w].rgbtBlue = round((old[h + 1][w - 1].rgbtBlue +
            //                                           old[h + 1][w].rgbtBlue +
            //                                           old[h][w - 1].rgbtBlue +
            //                                           old[h + 2][w - 1].rgbtBlue +
            //                                           old[h + 2][w].rgbtBlue +
            //                                           old[h + 2][w + 1].rgbtBlue +
            //                                           old[h][w].rgbtBlue +
            //                                           old[h][w + 1].rgbtBlue +
            //                                           old[h + 1][w + 1].rgbtBlue) / 9.0);

            //         // For bottom right corner - New Middle
            //         image[h + 1][w + 1].rgbtRed = round((old[h + 1][w + 1].rgbtRed +
            //                                              old[h][w + 2].rgbtRed +
            //                                              old[h + 1][w + 2].rgbtRed +
            //                                              old[h + 2][w + 2].rgbtRed +
            //                                              old[h + 2][w + 1].rgbtRed +
            //                                              old[h + 2][w].rgbtRed +
            //                                              old[h + 1][w].rgbtRed +
            //                                              old[h][w + 1].rgbtRed +
            //                                              old[h][w].rgbtRed) / 9.0);

            //         image[h + 1][w + 1].rgbtGreen = round((old[h + 1][w + 1].rgbtGreen +
            //                                               old[h][w + 2].rgbtGreen +
            //                                               old[h + 1][w + 2].rgbtGreen +
            //                                               old[h + 2][w + 2].rgbtGreen +
            //                                               old[h + 2][w + 1].rgbtGreen +
            //                                               old[h + 2][w].rgbtGreen +
            //                                               old[h + 1][w].rgbtGreen +
            //                                               old[h][w + 1].rgbtGreen +
            //                                               old[h][w].rgbtGreen) / 9.0);

            //         image[h + 1][w + 1].rgbtBlue = round((old[h + 1][w + 1].rgbtBlue +
            //                                               old[h + 1][w].rgbtBlue +
            //                                               old[h][w + 2].rgbtBlue +
            //                                               old[h + 1][w + 2].rgbtBlue +
            //                                               old[h + 2][w + 2].rgbtBlue +
            //                                               old[h + 2][w + 1].rgbtBlue +
            //                                               old[h + 2][w].rgbtBlue +
            //                                               old[h][w + 1].rgbtBlue +
            //                                               old[h][w].rgbtBlue) / 9.0);

            //         //far right new edge of old right corner
            //         image[h + 1][w + 2].rgbtRed = round((old[h][w + 1].rgbtRed +
            //                                              old[h][w + 2].rgbtRed +
            //                                              old[h + 1][w + 2].rgbtRed +
            //                                              old[h + 1][w + 1].rgbtRed +
            //                                              old[h + 2][w + 2].rgbtRed +
            //                                              old[h + 2][w + 1].rgbtRed) / 6.0);

            //         image[h + 1][w + 2].rgbtGreen = round((old[h][w + 1].rgbtGreen +
            //                                               old[h][w + 2].rgbtGreen +
            //                                               old[h + 1][w + 2].rgbtGreen +
            //                                               old[h + 1][w + 1].rgbtGreen +
            //                                               old[h + 2][w + 2].rgbtGreen +
            //                                               old[h + 2][w + 1].rgbtGreen) / 6.0);

            //         image[h + 1][w + 2].rgbtBlue = round((old[h][w + 1].rgbtBlue +
            //                                               old[h][w + 2].rgbtBlue +
            //                                               old[h + 1][w + 2].rgbtBlue +
            //                                               old[h + 1][w + 1].rgbtBlue +
            //                                               old[h + 2][w + 2].rgbtBlue +
            //                                               old[h + 2][w + 1].rgbtBlue) / 6.0);

            //         // Far bottom and below left corner - new Edge --> new corner
            //         image[h + 2][w - 1].rgbtRed = round((old[h + 1][w - 1].rgbtRed +
            //                                              old[h + 1][w].rgbtRed +
            //                                              old[h + 2][w - 1].rgbtRed +
            //                                              old[h + 2][w].rgbtRed) / 4.0);

            //         image[h + 2][w - 1].rgbtGreen = round((old[h + 1][w - 1].rgbtGreen +
            //                                               old[h + 1][w].rgbtGreen +
            //                                               old[h + 2][w - 1].rgbtGreen +
            //                                               old[h + 2][w].rgbtGreen) / 4.0);

            //         image[h + 2][w - 1].rgbtBlue = round((old[h + 1][w - 1].rgbtBlue +
            //                                               old[h + 1][w].rgbtBlue +
            //                                               old[h + 2][w - 1].rgbtBlue +
            //                                               old[h + 2][w].rgbtBlue) / 4.0);


            //         //Bottom - new left Edge
            //         image[h + 2][w].rgbtRed = round((old[h + 1][w - 1].rgbtRed +
            //                                          old[h + 1][w].rgbtRed +
            //                                          old[h + 2][w - 1].rgbtRed +
            //                                          old[h + 2][w].rgbtRed +
            //                                          old[h + 2][w + 1].rgbtRed +
            //                                          old[h + 1][w + 1].rgbtRed) / 6.0);

            //         image[h + 2][w].rgbtGreen = round((old[h + 1][w - 1].rgbtGreen +
            //                                           old[h + 1][w].rgbtGreen +
            //                                           old[h + 2][w - 1].rgbtGreen +
            //                                           old[h + 2][w].rgbtGreen +
            //                                           old[h + 2][w + 1].rgbtGreen +
            //                                           old[h + 1][w + 1].rgbtGreen) / 6.0);

            //         image[h + 2][w].rgbtBlue = round((old[h + 1][w - 1].rgbtBlue +
            //                                           old[h + 1][w].rgbtBlue +
            //                                           old[h + 2][w - 1].rgbtBlue +
            //                                           old[h + 2][w].rgbtBlue +
            //                                           old[h + 2][w + 1].rgbtBlue +
            //                                           old[h + 1][w + 1].rgbtBlue) / 6.0);

            //         // For bottom right edge -new
            //         image[h + 2][w + 1].rgbtRed = round((old[h + 1][w + 1].rgbtRed +
            //                                              old[h + 1][w + 2].rgbtRed +
            //                                              old[h + 2][w + 2].rgbtRed +
            //                                              old[h + 2][w + 1].rgbtRed +
            //                                              old[h + 2][w].rgbtRed +
            //                                              old[h + 1][w].rgbtRed) / 6.0);

            //         image[h + 2][w + 1].rgbtGreen = round((old[h + 1][w + 1].rgbtGreen +
            //                                               old[h + 1][w + 2].rgbtGreen +
            //                                               old[h + 2][w + 2].rgbtGreen +
            //                                               old[h + 2][w + 1].rgbtGreen +
            //                                               old[h + 2][w].rgbtGreen +
            //                                               old[h + 1][w].rgbtGreen) / 6.0);

            //         image[h + 2][w + 1].rgbtBlue = round((old[h + 1][w + 1].rgbtBlue +
            //                                               old[h + 1][w].rgbtBlue +
            //                                               old[h + 1][w + 2].rgbtBlue +
            //                                               old[h + 2][w + 2].rgbtBlue +
            //                                               old[h + 2][w + 1].rgbtBlue +
            //                                               old[h + 2][w].rgbtBlue) / 6.0);

            //         // new bottom right corner
            //         image[h + 2][w + 2].rgbtRed = round((old[h + 1][w + 2].rgbtRed +
            //                                              old[h + 1][w + 1].rgbtRed +
            //                                              old[h + 2][w + 2].rgbtRed +
            //                                              old[h + 2][w + 1].rgbtRed) / 4.0);

            //         image[h + 2][w + 2].rgbtGreen = round((old[h + 1][w + 2].rgbtGreen +
            //                                               old[h + 1][w + 1].rgbtGreen +
            //                                               old[h + 2][w + 2].rgbtGreen +
            //                                               old[h + 2][w + 1].rgbtGreen) / 4.0);

            //         image[h + 2][w + 2].rgbtBlue = round((old[h + 1][w + 2].rgbtBlue +
            //                                               old[h + 1][w + 1].rgbtBlue +
            //                                               old[h + 2][w + 2].rgbtBlue +
            //                                               old[h + 2][w + 1].rgbtBlue) / 4.0);
            //     }
            // }

        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    // for (int h = 1; h < height + 1 ; h ++)
    // {
    //     for (int w = 1; w < width +1; w ++)
    //     {
    //         printf("Red - %i , Green - %i , Blue - %i ;\n", old[h][w].rgbtRed , old[h][w].rgbtGreen , old[h][w].rgbtBlue );
    //     }
    // }
    for (int h = 1; h < new_h - 1 ; h++)
    {
        for (int w = 1, l = 0; w < new_w - 1 ; w++)
        {

            int rgx = (- (1 * old[h - 1][w - 1].rgbtRed) + (1 * old[h - 1][w + 1].rgbtRed) +
                       - (2 * old[h][w - 1].rgbtRed) + (2 * old[h][w + 1].rgbtRed) +
                       - (1 * old[h + 1][w - 1].rgbtRed) + (1 * old[h + 1][w + 1].rgbtRed));

            int rgy = (- (1  * old[h - 1][w - 1].rgbtRed) - (2 * old[h - 1][w].rgbtRed) - (1 * old[h - 1][w + 1].rgbtRed) +
                       (1 * old[h + 1][w - 1].rgbtRed) + (2 * old[h + 1][w].rgbtRed) + (1 * old[h + 1][w + 1].rgbtRed));

            int r = round(sqrt((rgx * rgx) + (rgy * rgy)));
            if (r > 255)
            {
                image[h - 1][w - 1].rgbtRed = (255);
            }
            else
            {
                image[h - 1][w - 1].rgbtRed = r;
            }


            int ggx = (- (1 * old[h - 1][w - 1].rgbtGreen) + (1 * old[h - 1][w + 1].rgbtGreen) +
                       - (2 * old[h][w - 1].rgbtGreen) + (2 * old[h][w + 1].rgbtGreen) +
                       - (1 * old[h + 1][w - 1].rgbtGreen) + (1 * old[h + 1][w + 1].rgbtGreen));

            int ggy = (- (1  * old[h - 1][w - 1].rgbtGreen) - (2 * old[h - 1][w].rgbtGreen) - (1 * old[h - 1][w + 1].rgbtGreen) +
                       (1 * old[h + 1][w - 1].rgbtGreen) + (2 * old[h + 1][w].rgbtGreen) + (1 * old[h + 1][w + 1].rgbtGreen));
            int g = round(sqrt((ggx * ggx) + (ggy * ggy)));
            if (g > 255)
            {

                image[h - 1][w - 1].rgbtGreen = 255;
            }
            else
            {
                image[h - 1][w - 1].rgbtGreen = g;
            }

            int bgx = (- (1 * old[h - 1][w - 1].rgbtBlue) + (1 * old[h - 1][w + 1].rgbtBlue) +
                       - (2 * old[h][w - 1].rgbtBlue) + (2 * old[h][w + 1].rgbtBlue) +
                       - (1 * old[h + 1][w - 1].rgbtBlue) + (1 * old[h + 1][w + 1].rgbtBlue));

            int bgy = (- (1  * old[h - 1][w - 1].rgbtBlue) - (2 * old[h - 1][w].rgbtBlue) - (1 * old[h - 1][w + 1].rgbtBlue) +
                       (1 * old[h + 1][w - 1].rgbtBlue) + (2 * old[h + 1][w].rgbtBlue) + (1 * old[h + 1][w + 1].rgbtBlue));

            int b = round(sqrt((bgx * bgx) + (bgy * bgy)));
            if (b > 255)
            {

                image[h - 1][w - 1].rgbtBlue = 255;
            }
            else
            {
                image[h - 1][w - 1].rgbtBlue = b;
            }

        }
    }

    return;
}
