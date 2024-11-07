// problem statement: Create a program that analyzes the readability of a given text using the Coleman-Liau index,
// a readability formula designed to indicate the reading grade level required to understand the text.
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string input);   //  prototype of function
int count_words(string input);     //  prototype of function
int count_sentences(string input); //  prototype of function
int main(void)
{
    string input = get_string("Text: "); // take string input
    int letters = count_letters(input);  // count of letters returned from count_letters function is
                                         // stored in letters variable
    int words = count_words(input); // count of words returned from count_words function is stored in words variable
    int sentences = count_sentences(input); // count of sentences returned from count_sentences function is stored in sentences variable

    float L = ((float) letters / (float) words) * 100.0; // calculating average number of letters per 100 words
    float S = ((float) sentences / (float) words) * 100.0; // calculating average number of sentences per 100 words
    float index = 0.0588 * L - 0.296 * S - 15.8; // calculating Coleman-Liau index of a text
    int roundedIndex = round(index); // rounding the Coleman-Liau index to the nearest integer

    if (roundedIndex < 1)  // condition to handle less than 1 case
    {
        printf("Before Grade 1\n");
    }
    else if (roundedIndex >= 16) // condition to handle 16 or more than 16 case
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", roundedIndex); // else print the rounded Coleman-Liau index
    }

    return 0;
}

int count_letters(string input) // function for counting letters
{
    int count = 0;
    int length = strlen(input);
    for (int i = 0; i < length; i++) // iterating from start to the length of input text
    {
        if (isalpha(input[i])) // if the character is a letter than increment letter count else do
                               // nothing
        {
            count++;
        }
    }
    return count;
}

int count_words(string input) // function for counting words
{
    int count = 0;
    int length = strlen(input);
    for (int i = 0; i < length; i++) // iterating from start to the length of input text
    {
        if (isspace(input[i])) // if there is a space then increment words count else do nothing
        {
            count++;
        }
    }
    return count + 1; // number of words are one more than number of spaces
}

int count_sentences(string input) // function for counting sentences
{
    int count = 0;
    int length = strlen(input);
    for (int i = 0; i < length; i++) // iterating from start to the length of input text
    {
        if (input[i] == '.' || input[i] == '!' ||
            input[i] == '?') // if there is a dot, exclamation mark, question mark then increment
                             // sentence count else do nothing
        {
            count++;
        }
    }
    return count;
}
