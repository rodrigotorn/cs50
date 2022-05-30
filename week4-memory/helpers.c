#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int mean_color = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = mean_color;
            image[i][j].rgbtRed = mean_color;
            image[i][j].rgbtGreen = mean_color;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image_copy[i][j].rgbtRed = image[i][j].rgbtRed;
            image_copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image_copy[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtRed = image_copy[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image_copy[i][width - j - 1].rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image_copy[i][j].rgbtRed = image[i][j].rgbtRed;
            image_copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_red = 0, sum_blue = 0, sum_green = 0, count = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k) < 0 || (i + k) >= height)
                    {
                        continue;
                    }
                    if ((j + l) < 0 || (j + l) >= width)
                    {
                        continue;
                    }
                    sum_red += image_copy[i + k][j + l].rgbtRed;
                    sum_blue += image_copy[i + k][j + l].rgbtBlue;
                    sum_green += image_copy[i + k][j + l].rgbtGreen;
                    count++;
                }
            }
            image[i][j].rgbtRed = round((float) sum_red / count);
            image[i][j].rgbtBlue = round((float) sum_blue / count);
            image[i][j].rgbtGreen = round((float) sum_green / count);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image_copy[i][j].rgbtRed = image[i][j].rgbtRed;
            image_copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_red_x = 0, sum_red_y = 0, red_g = 0;
            int sum_blue_x = 0, sum_blue_y = 0, blue_g = 0;
            int sum_green_x = 0, sum_green_y = 0, green_g = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k) < 0 || (i + k) >= height)
                    {
                        continue;
                    }
                    if ((j + l) < 0 || (j + l) >= width)
                    {
                        continue;
                    }
                    sum_red_x += image_copy[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    sum_red_y += image_copy[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    red_g = round(sqrt(pow(sum_red_x, 2) + pow(sum_red_y, 2)));
                    if (red_g > 255)
                    {
                        red_g = 255;
                    }
                    sum_blue_x += image_copy[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    sum_blue_y += image_copy[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                    blue_g = round(sqrt(pow(sum_blue_x, 2) + pow(sum_blue_y, 2)));
                    if (blue_g > 255)
                    {
                        blue_g = 255;
                    }
                    sum_green_x += image_copy[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    sum_green_y += image_copy[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    green_g = round(sqrt(pow(sum_green_x, 2) + pow(sum_green_y, 2)));
                    if (green_g > 255)
                    {
                        green_g = 255;
                    }
                }
            }
            image[i][j].rgbtRed = red_g;
            image[i][j].rgbtBlue = blue_g;
            image[i][j].rgbtGreen = green_g;
        }
    }
    return;
}