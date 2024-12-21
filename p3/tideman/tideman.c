#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 9
#define MAX_VOTERS 9999
#define RANK_COUNT 3
#define INT_SIZE 32
#define NAME_LENGTH 30

int sort(int values[], int length);
int check_cycle(int graph[][MAX_CANDIDATES], int i, int j, int length);

typedef struct
{
    char name[NAME_LENGTH];
} candidate;

candidate candidates[MAX_CANDIDATES];
int preferences[MAX_CANDIDATES][MAX_CANDIDATES];
int graph[MAX_CANDIDATES][MAX_CANDIDATES];

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
            int candidate_found = -1;

            // Quality of life so program doesn't end on accidental wrong candidate
            while (candidate_found < 0)
            {
                printf("Rank %d: ", rank);
                fgets(name_input, NAME_LENGTH + 1, stdin); // + 1 to account for the \n
                name_input[strcspn(name_input, "\n")] = 0; // replace the newline character if it exists

                // Find the candidate
                for (int k = 0; k < argc - 1; k++)
                {
                    // Check candiate wasn't already voted in the ballot or already found in this loop
                    if (candidate_was_voted[k] == 0 && candidate_found < 0 &&
                        strcmp(candidates[k].name, name_input) == 0)
                    {
                        candidate_found = k;
                        candidate_was_voted[k] = 1;
                    }
                }
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

    // Make pairs
    int pair_count = 0;
    int pairs[MAX_CANDIDATES][2];
    int pair_scores[MAX_CANDIDATES];
    int sorted_pairs[MAX_CANDIDATES][2];

    for (int i = 0; i < argc - 1; i++)
    {
        for (int j = 0; j < argc - 1; j++)
        {
            if (j > i && preferences[i][j] != preferences[j][i])
            {
                int source_index;
                int target_index;

                if (preferences[i][j] > preferences[j][i])
                {
                    source_index = i;
                    target_index = j;
                }
                else
                {
                    source_index = j;
                    target_index = i;
                }

                pairs[pair_count][0] = source_index;
                pairs[pair_count][1] = target_index;
                pair_scores[pair_count] = preferences[source_index][target_index];
                pair_count++;
            }
        }
    }

    // Print pairs
    printf("\nPairs:\n");
    for (int i = 0; i < pair_count; i++)
    {
        int source_index = pairs[i][0];
        int target_index = pairs[i][1];
        printf("%d, %d: %d\n", source_index, target_index, preferences[source_index][target_index]);
    }

    sort(pair_scores, pair_count);

    // Print sorted values
    printf("\nScores sorted:\n");
    for (int i = 0; i < pair_count; i++)
    {
        printf("%d ", pair_scores[i]);
    }
    printf("\n");

    // Assign to sorted_pairs
    int sorted_index = 0;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            int source_index = pairs[j][0];
            int target_index = pairs[j][1];
            int score = preferences[source_index][target_index];

            if (score == pair_scores[i])
            {
                sorted_pairs[sorted_index][0] = source_index;
                sorted_pairs[sorted_index][1] = target_index;
                sorted_index++;
            }
        }
    }

    // Print sorted pairs
    printf("\nPairs sorted:\n");
    for (int i = 0; i < pair_count; i++)
    {
        int source_index = sorted_pairs[i][0];
        int target_index = sorted_pairs[i][1];
        printf("%d, %d: %d\n", source_index, target_index, preferences[source_index][target_index]);
    }

    // Add edges to graph
    printf("\n");
    for (int i = 0; i < pair_count; i++)
    {
        if (check_cycle(graph, sorted_pairs[i][0], sorted_pairs[i][1], pair_count) == 0)
        {
            graph[sorted_pairs[i][0]][sorted_pairs[i][1]] = 1;
        }
        else
        {
            printf("Cycle found: %d, %d\n", sorted_pairs[i][0], sorted_pairs[i][1]);
        }
    }

    // Printing graph
    printf("\nGraph:\n");
    for (int i = 0; i < argc - 1; i++)
    {
        for (int j = 0; j < argc - 1; j++)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    // Get winner - finding 0 column
    int search_index = 0;
    int winner_flag = 0;

    while (winner_flag == 0 && search_index < pair_count)
    {
        int edge_flag = 0;

        for (int i = 0; i < pair_count; i++)
        {
            if (graph[i][search_index] == 1)
            {
                edge_flag = 1;
            }
        }

        if (edge_flag == 0)
        {
            winner_flag = 1;
        }
        else
        {
            search_index++;
        }
    }

    printf("\n");
    if (winner_flag == 1)
    {
        printf("Winner: %s\n", candidates[search_index].name);
    }
    else
    {
        printf("No winner\n");
    }
}

// Check recursively if adding an edge at i,j creates a cycle
int check_cycle(int graph[][MAX_CANDIDATES], int i, int j, int length)
{
    for (int k = 0; k < length; k++)
    {
        if (graph[j][k] == 1)
        {
            if (k == i)
            {
                return 1;
            }
            else
            {
                return check_cycle(graph, i, k, length);
            }
        }
    }

    return 0;
}

// Bubble sort algorithm to sort array in place
int sort(int values[], int length)
{
    for (int i = 0; i < length; i++)
    {
        int swap_flag = 0;

        for (int j = 0; j < length - 1; j++)
        {
            // < sorts from greater to lower
            if (values[j] < values[j + 1])
            {
                int temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
                swap_flag = 1;
            }
        }

        // Return early if no swaps made this pass
        if (swap_flag == 0)
        {
            return 0;
        }
    }

    return 0;
}
