#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int COUNT = 26;
const char a = 'a';
const char A = 'A';
const char z = 'z';
const char Z = 'Z';

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: substitution key\n");
        return 1;
    }

    char *key = argv[1];

    if (strlen(key) != COUNT)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // standardise key
    for (int i = 0; i < COUNT; i++)
    {
        key[i] = toupper(key[i]);
    }

    char text[128];
    char cipher[128];
    const int INPUT_SIZE = sizeof(text);

    printf("plaintext: ");
    fgets(text, INPUT_SIZE, stdin);
    text[strcspn(text, "\n")] = 0; // replace the newline character if it exists

    int length = strlen(text);

    for (int i = 0; i < length; i++)
    {
        char c = text[i];

        if (a <= c && c <= z)
        {
            int index = c - a;
            int difference = key[index] - A;
            cipher[i] = a + difference;
        }
        else if (A <= c && c <= Z)
        {
            int index = c - A;
            int difference = key[index] - A;
            cipher[i] = A + difference;
        }
        else
        {
            cipher[i] = c;
        }
    }

    printf("ciphertext: %s\n", cipher);
    return 0;
}
