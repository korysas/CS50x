#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // check command line arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage ./recover image\n");
        return 1;
    }

    // store filename of input image
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s\n", infile);
        return 2;
    }

    int bytes_read;
    uint8_t buffer[512];
    int no_jpegs_found = -1;
    char filename[100];
    bool is_jpeg_found = false;
    FILE *img;
    while ((bytes_read = fread(&buffer, 1, 512, inptr)) == 512)
    {
        // printf("%d\n", buffer[0]);
        // printf("%d\n", buffer[1]);
        // printf("%d\n", buffer[2]);
        // printf("%d\n", buffer[3]);
        // printf("\n");

        // start of a jpeg
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            no_jpegs_found++;
            printf("Found a jpeg!\n");
            printf("jpegs found: %d\n", no_jpegs_found);

            if (is_jpeg_found)
            {
                // close out previous jpeg and start a new one
                fclose(img);
                sprintf(filename, "%03i.jpg", no_jpegs_found);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    fprintf(stderr, "Could not open %s\n", filename);
                    return 2;
                }

                fwrite(&buffer, 1, 512, img);
            }
            else
            {
                // start of the first jpeg
                printf("Found first jpeg!\n");
                sprintf(filename, "%03i.jpg", no_jpegs_found);
                printf("creating: %s\n", filename);
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    fprintf(stderr, "Could not open %s\n", filename);
                    return 2;
                }

                fwrite(&buffer, 1, 512, img);

                is_jpeg_found = true;
            }
        }
        else
        {
            if (is_jpeg_found)
            {
                // add to the currently open jpeg file
                fwrite(&buffer, 1, 512, img);
            }
        }
    }

    fclose(img);

    return 0;
}