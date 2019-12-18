// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // store number to resize by and file names
    char resizeFactor = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    if (resizeFactor < 1 || resizeFactor > 100)
    {
        fprintf(stderr, "The resize factor must be between 1 and 100\n");
        return 1;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    int infilePadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    printf("\nBITMAPINFOHEADER: %lu, BITMATFILEHEADER: %lu", sizeof(BITMAPINFOHEADER), sizeof(BITMAPFILEHEADER));
    printf("\noriginal");
    printf("\npadding: %d", infilePadding);
    printf("\nbiWidth: %d", bi.biWidth);
    printf("\nbiHeight: %d", bi.biHeight);
    printf("\nbiSizeImage: %d", bi.biSizeImage);
    printf("\nbfSize: %d", bf.bfSize);



    // Calculate new width and height based on resize factor
    int previousWidth = bi.biWidth;
    int previousHeight = bi.biHeight;
    bi.biWidth *= resizeFactor;
    bi.biHeight *= resizeFactor;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    printf("\n\nUpdated");
    printf("\npadding: %d", padding);

    // Calculate new biSizeImage and bfSize
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);


    printf("\nbiWidth: %d", bi.biWidth);
    printf("\nbiHeight: %d", bi.biHeight);
    printf("\nbiSizeImage: %d", bi.biSizeImage);
    printf("\nbfSize: %d", bf.bfSize);



    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(previousHeight); i < biHeight; i++)
    {
        // duplicating row for resize
        for (int r = 0; r < resizeFactor; r++)
        {
            printf("\n\nrow %d, file position: %li", i, ftell(inptr));
            // iterate over pixels in scanline
            for (int j = 0; j < previousWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile multplied by resize factor
                for (int n = 0; n < resizeFactor; n++) {
                    printf("\n%d -> r: %d, g: %d, b: %d", j, triple.rgbtRed, triple.rgbtGreen, triple.rgbtBlue);
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                printf("\npadding 0x00");
                fputc(0x00, outptr);
            }

            // skip over padding, if any
            fseek(inptr, previousWidth * sizeof(RGBTRIPLE) * -1, SEEK_CUR);
        }


        // skip over padding, if any
        printf("\nskipping %i bytes to account for infile padding", infilePadding);
        fseek(inptr, infilePadding + (previousWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
