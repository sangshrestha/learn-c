#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 9
#define MAX_VOTERS 9999
#define RANK_COUNT 3
#define INT_SIZE 32
#define NAME_LENGTH 30

typedef struct
{
    char name[NAME_LENGTH];
} candidate;

candidate candidates[MAX_CANDIDATES];
int preferences[MAX_CANDIDATES][MAX_CANDIDATES] = {0};

int main(int argc, char *argv[])
{
    // Check args
    // Could additionally check it's at least RANK_COUNT
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }
    else if (argc > MAX_CANDIDATES + 1)
    {
        printf("Max candidates %d exceeded\n", MAX_CANDIDATES);
        return 2;
    }

    // Store candidates from args in an array
    for (int i = 0; i < argc - 1; i++)
    {
        if (strlen(argv[i + 1]) > NAME_LENGTH)
        {
            printf("Name for a candidate is too long\n");
            return 3;
        }
        strcpy_s(candidates[i].name, NAME_LENGTH, argv[i + 1]);
    }

    // Ask user for number of voters
    char voter_count_str[INT_SIZE];
    printf("Number of voters: ");
    fgets(voter_count_str, INT_SIZE, stdin);
    voter_count_str[strcspn(voter_count_str, "\n")] = 0;     // replace the newline character if it exists
    int voter_count_int = strtol(voter_count_str, NULL, 10); // returns 0 if error

    // Error check user input
    if (voter_count_int < 1)
    {
        printf("Invalid voter count");
        return 4;
    }
    else if (voter_count_int > MAX_VOTERS)
    {
        printf("Max voters %d exceeded", MAX_VOTERS);
        return 5;
    }

    // Cast ballots
    for (int i = 0; i < voter_count_int; i++)
    {
        printf("\nBallot #%d\n", i + 1);
        int candidate_was_voted[MAX_CANDIDATES] = {0};

        // Rank candidates
        for (int rank = 1; rank <= RANK_COUNT; rank++)
        {
            char name_input[NAME_LENGTH];

            printf("Rank %d: ", rank);
            fgets(name_input, NAME_LENGTH + 1, stdin); // + 1 to account for the \n
            name_input[strcspn(name_input, "\n")] = 0; // replace the newline character if it exists

            // Find the candidate
            int candidate_found = -1;

            for (int k = 0; k < argc - 1; k++)
            {
                // Check candiate wasn't already voted in the ballot or already found in this loop
                if (candidate_was_voted[k] == 0 && candidate_found < 0 && strcmp(candidates[k].name, name_input) == 0)
                {
                    candidate_found = k;
                    candidate_was_voted[k] = 1;
                }
            }

            if (candidate_found < 0)
            {
                printf("Invalid vote\n");
                return 6;
            }

            // Update preferences matrix
            for (int j = 0; j < argc - 1; j++)
            {
                if (candidate_was_voted[j] == 0)
                {
                    preferences[candidate_found][j]++;
                }
            }
        }

        printf("\n");
    }

    // Printing preferences matrix
    printf("\nPreferences matrix:\n");
    for (int i = 0; i < argc - 1; i++)
    {
        for (int j = 0; j < argc - 1; j++)
        {
            printf("%d ", preferences[i][j]);
        }
        printf("\n");
    }
}
