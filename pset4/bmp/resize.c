/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

#define MAX_SIZE 100

int size;

void replay(BITMAPFILEHEADER bfh, BITMAPINFOHEADER bhi, RGBTRIPLE scanline[], FILE* fp);

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // scale to resize
    size = atoi(argv[1]);

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    if (size < 1 || size > 100)
    {
        printf("%d not within 1-100 range \n", size);
        return 2;
    }

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
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

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    RGBTRIPLE scanline[bi.biWidth];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // read each triple into array
            scanline[j] = triple;

            // write RGB triple to outfile
            //fwrite(&triple, size * sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any

        /**
         * JW: If we didn't skip over the padding, then during the next iteration
         * instead of starting on a pixel, we'd be starting the scan line with padding.
         */
        fseek(inptr, padding, SEEK_CUR);

        // call replay function
        replay(bf, bi, scanline, outptr);
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

// replay must add the resized scanlines in the new outfile
void
replay (BITMAPFILEHEADER bfh, BITMAPINFOHEADER bih, RGBTRIPLE scanline[], FILE* fp)
{
    // length is the length of the scanline in pixels
    int length = bih.biWidth;
    BITMAPFILEHEADER bf = bfh;
    BITMAPINFOHEADER bi = bih;
    bi.biWidth *= size;
    bi.biHeight *= size;

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // http://stackoverflow.com/questions/25713117/what-is-the-difference-between-bisizeimage-bisize-and-bfsize
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // Only write header on the first call of this replay
    static int writeheader = 0;

    if (writeheader == 0)
    {
        // write outfile's BITMAPFILEHEADER
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, fp);

        // write outfile's BITMAPINFOHEADER
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, fp);

        writeheader = 1;
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < length; j++)
        {
            for (int k = 0; k < size; k++)
                // write RGB triple to outfile
                fwrite(&scanline[j], sizeof(RGBTRIPLE), 1, fp);
        }

        // add padding if any...
        for (int l = 0; l < padding; l++)
        {
            fputc(0x00, fp);
        }
    }
    return;
}