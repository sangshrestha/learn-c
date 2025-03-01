#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

#define HEADER_SIZE 44

int main(int argc, char *argv[])
{

    if (argc < 4)
    {
        printf("Usage: volume input.wav output.wav scale\n");
        return 1;
    }

    FILE *src = fopen(argv[1], "rb");
    FILE *dst = fopen(argv[2], "wb");
    float scale = strtof(argv[3], NULL);

    BYTE header[HEADER_SIZE];
    int16_t bb;

    fread(header, HEADER_SIZE, 1, src);
    fwrite(header, HEADER_SIZE, 1, dst);

    while (fread(&bb, sizeof(bb), 1, src) != 0)
    {
        bb = bb * scale;
        fwrite(&bb, sizeof(bb), 1, dst);
    }

    fclose(dst);
    fclose(src);
}
