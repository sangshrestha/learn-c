#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isIntString(char str[]);
char rot_char(char c, int key);

int main(int argc, char **argv)
{
    int isInt = isIntString(argv[1]);

    if (isInt && argc == 2)
    {
        int userKey = atoi(argv[1]);
        int key = userKey % 26;

        char text[128];
        char cipher[128];
        const int INPUT_SIZE = sizeof(text);

        printf("plaintext: ");
        fgets(text, INPUT_SIZE, stdin);
        text[strcspn(text, "\n")] = 0; // replace the newline character if it exists

        int length = strlen(text);

        // build the cipher string
        for (int i = 0; i < length; i++)
        {
            cipher[i] = rot_char(text[i], key);
        }
        cipher[length] = 0;

        printf("ciphertext: %s\n", cipher);
    }
    else
    {
        printf("Usage: caesar key\n");
    }
}

int isIntString(char str[])
{
    int len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        char c = str[i];

        if (c < 48 || 57 < c)
        {
            return 0;
        }
    }

    return 1;
}

char rot_char(char c, int key)
{
    if (97 <= c && c <= 122)
    {
        return 97 + (c - 97 + key) % 26;
    }
    else if (65 <= c && c <= 90)
    {

        return 65 + (c - 65 + key) % 26;
    }
    else
    {
        return c;
    }
}
