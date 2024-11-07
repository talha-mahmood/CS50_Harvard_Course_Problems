// problem: Create a program that conducts a plurality election by accepting candidate names,
// collecting votes, and printing the winner(s) with the highest votes
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    // Get the number of voters
    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");
        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Print the winner(s)
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    bool check = false;
    for (int i = 0; i < candidate_count; i++)
    {
        // Compare input name with candidate names
        if (strcmp(name, candidates[i].name) == 0)
        {
            check = true;
            candidates[i].votes++;
        }
    }
    // Return false if no matching candidate
    if (check == false)
    {
        return false;
    }
    return true;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int winner_votes = 0; // Initially set to the smallest value
    string winner_names[9];
    int winners_count = 0;

    // Find the maximum votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (winner_votes < candidates[i].votes)
        {
            winner_votes = candidates[i].votes;   // Update winner votes
            winner_names[0] = candidates[i].name; // Update winner name
        }
    }

    // Check if there is a winner name, increment winner count to 1
    if (winner_names[0])
    {
        winners_count++;
    }

    // Find candidates with votes equal to the maximum
    for (int i = 0; i < candidate_count; i++)
    {
        if (winner_votes == candidates[i].votes)
        {
            // we do not want to compare the winner with itself
            if (winner_names[0] != candidates[i].name)
            {
                // store name of candidate whose votes equal are to the winner votes
                winner_names[winners_count] = candidates[i].name;
                winners_count++;
            }
        }
    }

    // Print all winners
    for (int i = 0; i < winners_count; i++)
    {
        printf("%s\n", winner_names[i]);
    }

    return;
}
