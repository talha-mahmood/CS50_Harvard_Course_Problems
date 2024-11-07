// problem statement:  Task is to implement a substitution cipher, a encryption technique in which each letter of the plaintext is
// replaced with a corresponding letter in the provided key. The key must be a string of 26 unique alphabetical characters.

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Function prototypes
bool is_valid_key(string key);
char substitute(char c, string key);

int main(int argc, string argv[])
{
    // Check if the program is executed with exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1; // return 1 indicates error
    }

    // Validate the provided key
    string key = argv[1];
    if (!is_valid_key(key))
    {
        return 1; // return 1 indicating an error
    }

    // Prompt user for plaintext input
    string plaintext = get_string("plaintext: ");

    // Encrypt the plaintext using the substitution key
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        printf("%c", substitute(plaintext[i], key));
    }
    printf("\n");

    return 0;
}

// Function to check if the key is valid
bool is_valid_key(string key)
{
    // Check if the key has 26 characters
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    bool seen[26] = {false}; // this will be used to check if user has entered repeated characters or not

    // Iterate over each character in the key
    for (int i = 0; i < 26; i++)
    {
        // Check if the character is alphabetic
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetical characters.\n");
            return false;
        }

        // Check for duplicates by marking seen characters as true
        int index = toupper(key[i]) - 'A'; // Convert the character to uppercase and calculate its position in the alphabet (0 for 'A', 1 for 'B', etc.)
                                           // This is used to check for repeated characters by indexing into the seen array.
        if (seen[index]) // Check if the current character has already been seen (i.e., marked as true in the seen array).
        {
            printf("Key must not contain repeated characters.\n"); // Print an error message if a repeated character is found.
            return false;
        }
        seen[index] = true; // Mark the character as seen by setting the corresponding index in the seen array to true.
    }
    return true;
}

// Function to substitute a character using the key
char substitute(char c, string key)
{
    // Substitute if character is uppercase
    if (isupper(c))
    {
        return toupper(key[c - 'A']); // Get the character from the key at the position corresponding to the
                                      // plaintext character's position in the alphabet (c - 'A').
                                      // Convert the substituted character to uppercase
                                      // because the original plaintext character is uppercase.
    }
    // Substitute if character is lowercase
    else if (islower(c))
    {
        return tolower(key[c - 'a']); // Get the character from the key at the position corresponding to the
                                      // plaintext character's position in the alphabet (c - 'a').
                                      // Convert the substituted character to lowercase
                                      // because the original plaintext character is lowercase.
    }
    // Return non-alphabetic characters unchanged
    return c;
}
