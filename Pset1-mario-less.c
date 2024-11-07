// problem statement: make a right aligned pyramid using # based on height entered by the user
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
int main(void)
{
    int height = 0;
    do
    {
        height = get_int("Enter height from 1 to 8 to build pyramid ");
    }
    while (height < 1 || height > 8); //The loop continues until the user enters a valid height between 1 and 8.

    for (int i = 1; i <= height; i++) // Outer loop runs from 1 to the entered height, determining the current row number.
    {

        for (int j = 1; j <= height - i; j++) //Prints spaces before the # symbols to align the pyramid to the right.
        {
            printf(" ");
        }

        for (int k = 1; k <= i; k++)
        {
            printf("#"); // Prints # symbols
        }

        printf("\n"); // for moving to next line after printing each row.
    }
}
