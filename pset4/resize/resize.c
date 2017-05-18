/**
 * Copies a BMP piece by piece but resize along the way
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize factor infile outfile\n");
        return 1;
    }

    // get resize factor
    char *factor_string = argv[1];
    int factor = atoi(factor_string);

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
    printf("Size: %d\n", bi.biSize);
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

    // modify BITMAPINFOHEADER width and height
    bi.biWidth *= factor;
    bi.biHeight *= factor;
    bi.biSizeImage = bi.biWidth * abs(bi.biHeight) * sizeof(RGBTRIPLE);

    // modify BITMAPFILEHEADER
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage;

    printf("\n\n");
    printf("Width: %d\n", bi.biWidth);
    printf("Height: %d\n", bi.biHeight);
    printf("Size: %d\n", bi.biSize);
    printf("Size Image: %d\n", bi.biSizeImage);
    printf("File Size: %d\n", bf.bfSize);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            // if (j % 2 == 0)
            // {
            //     triple.rgbtBlue = 0x00;
            //     triple.rgbtGreen = 0x00;
            //     triple.rgbtRed = 0xff;
            // }
            // else
            // {
            //     triple.rgbtBlue = 0xff;
            //     triple.rgbtGreen = 0x00;
            //     triple.rgbtRed = 0x00;
            // }

            RGBTRIPLE const_color;
            const_color.rgbtBlue = 0xff;
            const_color.rgbtGreen = 0x00;
            const_color.rgbtRed = 0x00;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            for (int l = 0; l < factor; l++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                
                long position = ftell(outptr);
                fseek(outptr, padding + bi.biWidth, SEEK_CUR);
                fwrite(&const_color, sizeof(RGBTRIPLE), 1, outptr);
                fseek(outptr, position, SEEK_SET);
            }
            
            // for (int k = 0; k < factor - 1; k++)
            // {
            //     fseek(outptr, padding + bi.biWidth, SEEK_CUR);
            //     for (int m = 0; m < factor; m++)
            //         fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            // }
            // fseek(outptr, position, SEEK_SET);
        }

        // skip over padding, if any
        for (int n = 0; n < factor; n++)
        {
            fseek(inptr, padding + bi.biWidth, SEEK_CUR);
        }

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
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
