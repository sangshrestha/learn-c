#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    char name[31];
    int votes;
} candidate;

void print_candidates(candidate candidates[]);

// Array of candidates
candidate candidates[MAX];

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Assign candidates from args
    for (int i = 0; i < argc; i++)
    {
        strcpy_s(candidates[i].name, 31, argv[i + 1]);
        candidates[i].votes = 0;
    }

    char voter_count[3];
    const int INPUT_SIZE = sizeof(voter_count);

    printf("Number of voters: ");
    fgets(voter_count, INPUT_SIZE, stdin);
    voter_count[strcspn(voter_count, "\n")] = 0; // replace the newline character if it exists

    int voter_count_int = (int)strtol(voter_count, NULL, 10);
    int max_vote = 0;

    for (int i = 0; i < voter_count_int; i++)
    {
        char vote[31];
        const int INPUT_SIZE = sizeof(vote);

        printf("Vote: ");
        fgets(vote, INPUT_SIZE, stdin);
        vote[strcspn(vote, "\n")] = 0; // replace the newline character if it exists

        // Loop through candidate to add vote
        int candidate_found = -1;

        for (int i = 0; i < MAX; i++)
        {
            if (strcmp(vote, candidates[i].name) == 0)
            {
                candidate_found = i;
                candidates[i].votes += 1;
                if (candidates[i].votes > max_vote)
                {
                    max_vote = candidates[i].votes;
                }
            }
        }

        if (candidate_found == -1)
        {
            printf("Invalid vote.\n");
        }
    }

    // Get Winners
    for (int i = 0; i < MAX; i++)
    {
        if (candidates[i].votes == max_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }
}

void print_candidates(candidate candidates[])
{
    for (int i = 0; i < MAX; i++)
    {
        printf("%s: %d\n", candidates[i].name, candidates[i].votes);
    }
}
