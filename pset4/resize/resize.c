/**
 * Copies a BMP piece by piece but resize along the way
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

/**
 * function to enlrage a bitmap
 */
//void enlarge()

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // get resize factor
    float factor = atof(argv[1]);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

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

    // debug purposes get size information of file
    printf("Width: %d\n", bi.biWidth);
    printf("Height: %d\n", bi.biHeight);
    printf("Size Image: %d\n", bi.biSizeImage);
    printf("File Size: %d\n", bf.bfSize);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for original input file
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // modify BITMAPINFOHEADER width and height
    BITMAPINFOHEADER bi_resize;
    bi_resize = bi;
    bi_resize.biWidth = bi.biWidth * factor;
    bi_resize.biHeight = bi.biHeight * factor;

    // determine padding for the resized output file
    int padding_resize = (4 - (bi_resize.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // printf("padding: %d\n", padding_resize);

    bi_resize.biSizeImage = (sizeof(RGBTRIPLE) * bi_resize.biWidth) * abs(bi_resize.biHeight);

    // modify BITMAPFILEHEADER
    BITMAPFILEHEADER bf_resize;
    bf_resize = bf;
    bf_resize.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi_resize.biSizeImage;

    printf("\n");
    printf("Width: %d\n", bi_resize.biWidth);
    printf("Height: %d\n", bi_resize.biHeight);
    printf("Size Image: %d\n", bi_resize.biSizeImage);
    printf("File Size: %d\n\n", bf_resize.bfSize);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_resize, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_resize, sizeof(BITMAPINFOHEADER), 1, outptr);

    long start_position = ftell(inptr);

    int row = 0;
    // iterate over infile's scanlines
    for (int i = 0, height = abs(bi_resize.biHeight); i < height; i++)
    {
        row = i / factor;
        printf("in row: %d\tout row: %d\n", row, i);
        fseek(inptr, start_position + (bi.biWidth * sizeof(RGBTRIPLE) + padding) * row, SEEK_SET);

        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // RGBTRIPLE blue;
            // blue.rgbtBlue = 0xff;
            // blue.rgbtGreen = 0x00;
            // blue.rgbtRed = 0x00;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            for (int l = 0; l < factor; l++)
            {  
                // horizontal scaling
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        // skip over padding of the infile
        // fseek(inptr, padding, SEEK_CUR);

        // add padding to the outfile
        for (int k = 0; k < padding_resize; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
