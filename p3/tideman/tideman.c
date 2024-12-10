#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 9
#define MAX_VOTERS 9999
#define INT_SIZE 32
#define NAME_LENGTH 31

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
        printf("Max candidates %d exceeded", MAX_CANDIDATES);
        return 2;
    }

    // Ask user for number of voters
    char voter_count_str[INT_SIZE];
    printf("Number of voters: ");
    fgets(voter_count_str, INT_SIZE, stdin);
    voter_count_str[strcspn(voter_count_str, "\n")] = 0;     // replace the newline character if it exists
    int voter_count_int = strtol(voter_count_str, NULL, 10); // returns 0 if error

    // Error check user input
    if (voter_count_int == 0)
    {
        printf("Invalid voter count");
        return 3;
    }
    else if (voter_count_int > MAX_VOTERS)
    {
        printf("Max voters %d exceeded", MAX_VOTERS);
        return 4;
    }
}