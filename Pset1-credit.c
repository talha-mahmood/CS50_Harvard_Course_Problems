// problem statement:determine the type of a credit card (AMEX, MASTERCARD, or VISA) based on its number and check the validity of the card
// using luhn's algorithm
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long credit_card_no = get_long("Number: ");


    int arr[50];
    int remainder;
    int index = 0;
    int count = 0;

    while (credit_card_no != 0)
    {
        // code for storing individual digits in an array and storing length of array
        remainder = credit_card_no % 10;//extracts the last digit of the number.
        arr[index] = remainder; // stores the number in an array
        index++;
        count++;// track number of digits stored
        credit_card_no = credit_card_no / 10; // remove the last digit from the number so that we can store the next digit
    }

    if (count < 13 || count > 16)
    {
        printf("INVALID\n"); // credit card number length is not between 13 and 16 inclusive
        return 0;
    }



    int arr2[50];
    int index2 = 0;
    int sum = 0;
    int sum2 = 0;
    int finalsum = 0;
    // Iterates through every second digit starting from the second-to-last digit multiply it by 2 and then sums all digits
    for (int j = 1; j < index; j = j + 2)
    {
        if ((arr[j] * 2) >= 10) // if digits of a number is more than one then we have to sum individual digits of a number
        {
            sum = sum + (arr[j] * 2) % 10 +
                  (arr[j] * 2) / 10; // taking out 1st and 2nd digit from number and sum the digits
        }
        else
        {
            sum = sum + arr[j] * 2; // simply if there is one digit in number then multiply by 2 and add to sum
        }
    }

    for (int k = 0; k < index; k = k + 2) // iterate through the remaining alternate digits starting from last
    {
        sum2 = sum2 + arr[k]; // summation of remaining digits
    }
    finalsum = sum + sum2;

    if (finalsum % 10 != 0)
    {
        printf("INVALID\n"); //  validity of Luhn’s Algorithm
        return 0;
    }

    // check AMEX number should start from 34 or 37 and total digits should be 15
    if ((arr[index - 1] == 3 && (arr[index - 2] == 4 || arr[index - 2] == 7)) && count == 15)
    {
        printf("AMEX\n");
    }
    // check MASTERCARD number should start from 51,52,53,54 or 55 and total digits should be 16
    else if ((arr[index - 1] == 5 &&
              (arr[index - 2] == 1 || arr[index - 2] == 2 || arr[index - 2] == 3 ||
               arr[index - 2] == 4 || arr[index - 2] == 5)) &&
               count == 16)
    {
        printf("MASTERCARD\n");
    }
    // check VISA number should start from 4 and total digits should be 13 or 16
    else if (arr[index - 1] == 4 && (count == 13 || count == 16))
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n"); // Not a AMEX, Visa or Mastercard
    }
}
