import csv
import sys

def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Invalid Command line arguments")
        exit(1)

    # Read database file into a variable
    with open(sys.argv[1], newline='') as csvfile:
        reader = csv.reader(csvfile)
        # Get the header row
        header = next(reader)
        # Extract everything after 'name' in the header row
        dna_subsequences = header[1:]  # Skip the 'name' column

    # Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as dna_sequence_file:
        dna_sequence = dna_sequence_file.read()

    # Find longest match of each STR in DNA sequence
    # We will store the longest runs for each STR in a dictionary
    longest_runs = {}
    for dna_subsequence in dna_subsequences:
        longest_run = longest_match(dna_sequence, dna_subsequence)
        longest_runs[dna_subsequence] = longest_run

    # Check database for matching profiles
    with open(sys.argv[1], newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            match = True
            # Check if all STR counts match for this person
            for dna_subsequence in dna_subsequences:
                if int(row[dna_subsequence]) != longest_runs[dna_subsequence]:
                    match = False
                    break  # No need to check further if any STR doesn't match

            # If all STR counts matched, print the person's name and exit
            if match:
                print(row['name'])
                return

    # If no match was found after checking all rows
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    return longest_run


main()
