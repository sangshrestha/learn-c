#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 9
#define MAX_VOTERS 9999
#define INT_SIZE 32
#define NAME_LENGTH 30

typedef struct
{
    char name[NAME_LENGTH];
} candidate;

candidate candidates[MAX_CANDIDATES];

int main(int argc, char *argv[])
{
    // Check args
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
    for (int i = 1; i < argc; i++)
    {
        if (strlen(argv[i]) > NAME_LENGTH)
        {
            printf("Name for a candidate is too long\n");
            return 3;
        }
        strcpy_s(candidates[i].name, NAME_LENGTH, argv[i]);
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
}
