#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // validate number of command line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    char *sourceFileName = argv[1];

    // open source file to recover
    FILE *sourceFile = fopen(sourceFileName, "r");
    if (sourceFile == NULL)
    {
        fprintf(stderr, "Could not open source file, please enter correct source file name\n");
        return 2;
    }

    // create a variable (buffer) to store the values, but what type?
    // int *buffer = malloc(512 * sizeof(BYTE));
    BYTE buffer[512];
    bool eof = false;
    int fileCount = 1;
    char filename[8];
    FILE *imageFile = NULL;

    while (!eof)
    {
        size_t blockSize = fread(&buffer, 1, 512, sourceFile);
        if (blockSize < 512)
        {
            eof = true;
        }

        // this is the beginning of an image
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            // if a previous file exists then close it
            if (imageFile != NULL)
            {
                fclose(imageFile);
            }

            // create a new file
            sprintf(filename, "%03i.jpg", fileCount);
            imageFile = fopen(filename, "w");
            if (imageFile == NULL)
            {
                fprintf(stderr, "Could not write image file\n");
                return 3;
            }
            fileCount++;
            printf("Found image file %s\n", filename);
            // FILE *img = fwrite(filename, "w");
        }

        if (imageFile != NULL)
        {
            fwrite(&buffer, 1, 512, imageFile);
        }
    };

    fclose(sourceFile);
}
