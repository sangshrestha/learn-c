#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculate_points(char c);

const int POINTS_TABLE[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 5, 8, 4, 10};

int main(void)
{
    char words[2][32];
    const int PLAYER_COUNT = 2;
    const int INPUT_SIZE = sizeof(words[0]);

    // get the 2 words from the user
    for (int i = 0; i < PLAYER_COUNT; i++)
    {
        printf("Player %i: ", i + 1);
        fgets(words[i], INPUT_SIZE, stdin);
        words[i][strcspn(words[i], "\n")] = 0; // replace the newline character if it exists
    }

    // calculate the points for the 2 words
    int points[2] = {0, 0};
    for (int i = 0; i < PLAYER_COUNT; i++)
    {
        int length = strlen(words[i]);

        for (int j = 0; j <= length; j++)
        {
            points[i] = points[i] + calculate_points(words[i][j]);
        }
    }

    printf("%i, %i\n", points[0], points[1]);

    if (points[0] > points[1])
    {
        printf("Player 1 wins!\n");
    }
    else if (points[0] < points[1])
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }

    return 0;
}

int calculate_points(char c)
{
    char upperC = toupper(c);

    if (65 <= upperC && upperC <= 90)
    {
        return POINTS_TABLE[toupper(c) - 65];
    }
    else
    {
        return 0;
    }
}