import re
import math

def main():
    # Get input from the user
    text = input("Text: ")

    # Calculate number of letters, words, and sentences
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Calculate average number of letters per 100 words
    L = (letters / words) * 100

    # Calculate average number of sentences per 100 words
    S = (sentences / words) * 100

    # Calculate Coleman-Liau index
    index = 0.0588 * L - 0.296 * S - 15.8
    rounded_index = round(index)

    # Output the readability grade
    if rounded_index < 1:
        print("Before Grade 1")
    elif rounded_index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {rounded_index}")


# Function to count letters in the text
def count_letters(text):
    count = 0
    for char in text:
        # Check if character is a letter
        if char.isalpha():
            count += 1
    return count

# Function to count words in the text
def count_words(text):
    count = 0
    # Splitting text by spaces gives a list of words
    for char in text:
        if char.isspace():
            count += 1
    # Number of words is one more than number of spaces
    return count + 1

# Function to count sentences in the text
def count_sentences(text):
    count = 0
    # Count periods, exclamations, and question marks as sentence terminators
    for char in text:
        if char in ['.', '!', '?']:
            count += 1
    return count

main()
