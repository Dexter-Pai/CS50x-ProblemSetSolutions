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
    int winnerYN;
}
candidate;

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
        candidates[i].winnerYN = 0;
    }

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

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) != 0)
        {
            // debug here printf("notequal.%i\n",i);
        }
        else
        {
            candidates[i].votes++;
            return true;
        }
    }
    // debug here printf("equal.\n");
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    candidate winner[MAX];
    winner[0].name = candidates[0].name;   //first one is always assumed winner
    winner[0].winnerYN = 1;                //this determines if the candidate is a winner or not
    int winnerVotes = candidates[0].votes; //first one is always assumed winner
    int winnerCounter = 0;                 //index of winner, will reset when new winner appear
    for (int i = 0; i < (candidate_count - 1); i++)
    {
        //if winner votes more than the first winner appear
        if (winnerVotes < candidates[i + 1].votes)
        {
            //clear the winner array first, so we can restart the winner value
            for (int j = 0; j < candidate_count; j++)
            {
                winner[j].name = "";
                winner[j].winnerYN = 0;
                winnerCounter = 0;
            }
            winner[winnerCounter].name = candidates[i + 1].name;
            winnerVotes = candidates[i + 1].votes;
            winner[winnerCounter].winnerYN = 1;
        }
        //if winner is more than one
        else if (winnerVotes == candidates[i + 1].votes)
        {
            winnerCounter++;
            winner[winnerCounter].name = candidates[i + 1].name;
            winner[winnerCounter].winnerYN = 1;
        }
    }

    //print winners
    for (int i = 0; i < candidate_count; i++)
    {
        if (winner[i].winnerYN == 1)
        {
            printf("%s\n", winner[i].name);
        }
    }

    // return;
}

/*
logic pseudocode
check if next candidate has more votes
if it has more, clean the names, record highest vote, record name
check next candidate
if it has more, record highest vote, record name
if it's the same, record the other name
*/
