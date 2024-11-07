// problem: Create a program to apply grayscale, sepia, reflection, or blur filters to a BMP image,
// then output the modified image
// helpers.c: make grayscale, sepia, reflection, and blur filter functions
#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average of the red, green, and blue values to convert to grayscale
            float grayscale_conversion = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            int rounded_grayscale = round(grayscale_conversion);

            // Assign the grayscale value to all color channels (R, G, B)
            image[i][j].rgbtBlue = rounded_grayscale;
            image[i][j].rgbtGreen = rounded_grayscale;
            image[i][j].rgbtRed = rounded_grayscale;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate sepia color values based on the formula
            float sepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            float sepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            float sepiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;

            // Round the sepia values and ensure they don't exceed the maximum value of 255
            int rounded_sepiaRed = round(sepiaRed);
            int rounded_sepiaGreen = round(sepiaGreen);
            int rounded_sepiaBlue = round(sepiaBlue);
            if (rounded_sepiaRed > 255) rounded_sepiaRed = 255;
            if (rounded_sepiaGreen > 255) rounded_sepiaGreen = 255;
            if (rounded_sepiaBlue > 255) rounded_sepiaBlue = 255;

            // Assign sepia values to the pixel
            image[i][j].rgbtBlue = rounded_sepiaBlue;
            image[i][j].rgbtGreen = rounded_sepiaGreen;
            image[i][j].rgbtRed = rounded_sepiaRed;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary array to store the reflected image
    RGBTRIPLE temp[height][width];

    // Copy the image into the temp array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j].rgbtBlue = image[i][j].rgbtBlue;
            temp[i][j].rgbtGreen = image[i][j].rgbtGreen;
            temp[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    // Reflect the image by reversing the pixel order for each row
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][width - j - 1].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][width - j - 1].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][width - j - 1].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary array to store the blurred image
    RGBTRIPLE temp[height][width];

    // Iterate over each pixel in the image
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int sumR = 0, sumG = 0, sumB = 0;
            int count = 0;

            // Loop through neighboring pixels (including the current pixel itself)
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    // Neighbor pixel's x-coordinate
                    int nx = x + i;
                    // Neighbor pixel's y-coordinate
                    int ny = y + j;

                    // Ensure the neighbor pixel is within bounds
                    if (nx >= 0 && nx < height && ny >= 0 && ny < width)
                    {
                        // Accumulate the RGB values from neighboring pixels and pixel itself
                        sumR += image[nx][ny].rgbtRed;
                        sumG += image[nx][ny].rgbtGreen;
                        sumB += image[nx][ny].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average color values which will make the image blurred and store them in the temp array
            temp[x][y].rgbtRed = round(sumR / (float)count);
            temp[x][y].rgbtGreen = round(sumG / (float)count);
            temp[x][y].rgbtBlue = round(sumB / (float)count);
        }
    }

    // Copy the blurred image from the temp array back to the original image
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = temp[x][y];
        }
    }
}
