#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9
#define RANK_TOTAL 3
#define MAX_VOTERS 9
#define NAME_LENGTH 31

// Candidates have name and vote count
typedef struct
{
    char name[NAME_LENGTH];
    int votes;
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
        strcpy_s(candidates[i].name, NAME_LENGTH, argv[i + 1]);
        candidates[i].votes = 0;
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

        // Loop for ballot
        for (int j = 0; j < RANK_TOTAL; j++)
        {
            char vote[NAME_LENGTH];
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
                    strcpy_s(ballots[i].candidates[j].name, NAME_LENGTH, candidates[k].name);
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

    // Count ballots
    int max_vote = 0;
    int runoff = 1;

    for (int k = 0; k < RANK_TOTAL; k++)
    {

        if (runoff == 1)
        {
            for (int i = 0; i < voter_count_int; i++)
            {

                int ignore_rank = 0;

                for (int rank_count = 0; rank_count < RANK_TOTAL; rank_count++)
                {
                    char ballot_candidate[NAME_LENGTH];
                    strcpy_s(ballot_candidate, NAME_LENGTH, ballots[i].candidates[rank_count].name);

                    if (ignore_rank == 0)
                    {
                        // check not in ignored list
                        for (int j = 0; j < argc - 1; j++)
                        {
                            if (strcmp(ballot_candidate, candidates[j].name) == 0 && candidates[j].votes > -1)
                            {
                                // Add vote count
                                candidates[j].votes += 1;

                                if (candidates[j].votes > max_vote)
                                {
                                    max_vote = candidates[j].votes;
                                }

                                ignore_rank = 1;
                            }
                        }
                    }
                }
            }

            if (max_vote * 2 <= voter_count_int && k < RANK_TOTAL - 1)
            {

                printf("runoff\n");

                int least_vote = voter_count_int;

                for (int i = 0; i < argc - 1; i++)
                {
                    if (candidates[i].votes > -1 && candidates[i].votes < least_vote)
                    {
                        least_vote = candidates[i].votes;
                    }
                }

                for (int i = 0; i < argc - 1; i++)
                {
                    if (candidates[i].votes > -1)
                    {
                        if (candidates[i].votes == least_vote && least_vote != max_vote)
                        {
                            candidates[i].votes = -1;
                        }
                        else
                        {
                            candidates[i].votes = 0;
                        }
                    }
                }

                max_vote = 0;
            }
            else
            {
                runoff = 0;
            }
        }
    }

    // Print Winners
    for (int i = 0; i < argc - 1; i++)
    {
        if (candidates[i].votes == max_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return 0;
}
