#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];
/////vote from candidates array

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
void reset_votes(void);
bool elimination_check(int position);
int remaining_candidates(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) != 0)
        {
            // debug here printf("notequal.%i\n",i);
        }
        else
        {
            // candidates[i].votes++;
            preferences[voter][rank] = i; //// voter 0 rank 0 mhar candidate index number i
            return true;
        }
    }
    // debug here printf("equal.\n");
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    /*
    Pseudocode
    if eliminated, go to next rank in array
    if not eliminated,
    vote count of the candidate updated
    preferences[i][0]
    */

    //
    //reset votes function
// reset_votes();
    //while (test)
    //if eleminated = 1, return;

// for (int j = 0; j < candidate_count; j++)
    for (int i = 0; i < voter_count; i++)
    {
        int position = 0;
        while (elimination_check(preferences[i][position]))
        {
            position++;
        }

        candidates[preferences[i][position]].votes++;
        position = 0;
     }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int whichCandidate = 0;
    if (elimination_check(whichCandidate))
    {
        whichCandidate++;
    }
    int minimum = candidates[whichCandidate].votes;

    for (int i = 0; i < candidate_count - 1; i++)
    {

        if (candidates[i + 1].eliminated != true)
        {
            if (minimum < candidates[i + 1].votes);
            else
            {
                minimum = candidates[i + 1].votes;
            }
        }
    }
    return minimum;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int min_counter = 0;
    int remaining = remaining_candidates();
    for (int i = 0; i < candidate_count; i++)
    {
        if (min == candidates[i].votes)
        {
            min_counter++;
        }
    }
    if (min_counter == 1)
    {
        return false;
    }
    else if (min_counter > 1 && min_counter != remaining)
    {
        return false;
    }
    else if (min_counter == remaining)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (min == candidates[i].votes)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}

void reset_votes(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }
}

bool elimination_check(int position)
{
    // if (candidates[position].eliminated == true)
    // {
    //     position++;
    //     elimination_check(position);
    // }else if (candidates[position].eliminated == false)
    //     return position;
    //     else return position;

    if (candidates[position].eliminated == true)
    {
        return true;
    }
    return false;


    // if (candidates[position].eliminated == false)
    // return position;
    // while (candidates[position].eliminated == true)
    // {
    //     position++;
    //     elimination_check(position);
    // }
    // return position;
}

int remaining_candidates(void)
{
    int remaining = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            remaining++;
        }
    }
    return remaining;
}