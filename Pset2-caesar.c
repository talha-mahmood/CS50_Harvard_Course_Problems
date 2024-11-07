// problem statement: The task is to implement a program that encrypts messages using Caesar's cipher.
// Caesar's cipher is a encryption technique where each letter in the plaintext is shifted by a fixed number of positions.
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string argument); // prototype of function
char rotate(char plain_text_letter, int key); // prototype of function

int main(int argc, string argv[])
{
    int key = 0;
    string argument = argv[1]; // storing argument enterd by user in command line in argument variable
    if(argc == 2 ) // condition to check only one argument should exist not less not more
    {

        if(!only_digits(argument)) // conditional handling case when input is not a digit
        {
          printf("Usage: ./caesar key\n");
          return 1;
        }

        key = atoi(argument); // because the argument is of string type so converting it to int through atoi (ASCII To Integer)
    }
    else
    {
        printf("Usage: ./caesar key\n"); // conditional to handle case when argument entered is less than or greater than one
        return 1;
    }


    string plain_text = get_string("plaintext:  "); // getting plain text input from user
    string cipher_text = plain_text; // as cipher_text is of same length as of plain_text so initializing ciphertext variable with plain_text
    // loop for encrypting the plain text
    for (int i = 0; i < strlen(plain_text); i++)
    {
       cipher_text[i] = rotate( plain_text[i], key); // returning encrypted text and storing it in cipher_text variable
    }

    printf("ciphertext: %s\n",cipher_text); // printing cipher_text
    return 0;

}

bool only_digits(string argument) // function to check input argument is a digit or not
{
      for ( int i = 0; i < strlen(argument); i++) // runs from start to the length of argument
        {
            if (argument[i]>='0' && argument[i]<='9') // checking argument is a integer or not
            {
                // do nothing

            }
            else{

                return false; // not a integer return false
            }

        }

        return true;

}

char rotate(char plain_text_letter, int key) // function to rotate input plaintext based upon entered key
{
     char cipher_text_letter;
    // Only shift alphabetic characters
        if (isalpha(plain_text_letter))
        {
            char offset = isupper(plain_text_letter) ? 'A' : 'a'; // condition checking the case type of plain text to make offset of that case
            cipher_text_letter = ((plain_text_letter - offset + key) % 26) + offset; // formula to convert input text to cipher text using key and modulus 26
            return cipher_text_letter ;
        }
        else
        {
            // Non-alphabetic characters remain unchanged
            cipher_text_letter = plain_text_letter;
            return cipher_text_letter;
        }
}
