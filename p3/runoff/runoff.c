#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9
#define RANK_TOTAL 3
#define MAX_VOTERS 9

// Candidates have name and vote count
typedef struct
{
    char name[31];
} candidate;

// Ballot
typedef struct
{
    candidate candidates[RANK_TOTAL];
} ballot;

// Array of candidates
candidate candidates[MAX];

// Array of ballots
ballot ballots[MAX_VOTERS];

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }
    else if (argc > MAX)
    {
        printf("Max candidates %d exceeded", MAX);
        return 2;
    }

    // Assign candidates from args
    for (int i = 0; i < argc; i++)
    {
        // Assign name
        strcpy_s(candidates[i].name, 31, argv[i + 1]);
    }

    char voter_count[3];
    const int INPUT_SIZE = sizeof(voter_count);

    printf("Number of voters: ");
    fgets(voter_count, INPUT_SIZE, stdin);
    voter_count[strcspn(voter_count, "\n")] = 0; // replace the newline character if it exists

    int voter_count_int = (int)strtol(voter_count, NULL, 10);

    // Loop for number of votes
    for (int i = 0; i < voter_count_int; i++)
    {

        // Loop for ranks
        for (int j = 0; j < RANK_TOTAL; j++)
        {
            char vote[31];
            const int INPUT_SIZE = sizeof(vote);

            printf("Rank %d: ", j + 1);
            fgets(vote, INPUT_SIZE, stdin);
            vote[strcspn(vote, "\n")] = 0; // replace the newline character if it exists

            // Loop through candidate to add vote
            int candidate_found = -1;

            for (int k = 0; k < MAX; k++)
            {
                if (strcmp(vote, candidates[k].name) == 0)
                {
                    candidate_found = i;
                    strcpy_s(ballots[i].candidates[j].name, 31, candidates[k].name);
                }
            }

            if (candidate_found == -1)
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        printf("\n");
    }

    // Print Winners
    for (int i = 0; i < MAX_VOTERS; i++)
    {
        if (strlen(ballots[i].candidates[0].name) > 0)
        {

            printf("1) %s 2) %s 3) %s\n", ballots[i].candidates[0].name, ballots[i].candidates[1].name,
                   ballots[i].candidates[2].name);
        }
    }

    return 0;
}
