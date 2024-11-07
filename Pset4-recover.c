// Recover JPEG images from a memory card by detecting headers and saving each image in 512-byte blocks,
// handling multiple files efficiently.
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Block size for FAT file system
int blocksize = 512;

int main(int argc, char *argv[])
{
    // Ensure the user enters exactly one argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open memory card file
    FILE *memory_card_rawfile = fopen(argv[1], "r");
    if ( memory_card_rawfile == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Dynamically allocate memory for the buffer using malloc
    uint8_t *buffer = malloc(blocksize * sizeof(uint8_t));
    // Check if memory allocation succeeded
    if (buffer == NULL)
    {
        printf("Could not allocate memory for the buffer.\n");
        fclose(memory_card_rawfile);
        return 1;
    }

    FILE *jpeg_img = NULL;
    char jpeg_name[8];
    int count_file = 0;
    int jpeg_detected = 0;

    // Read blocks of 512 bytes until the end of the card.raw file
    while (fread(buffer, sizeof(uint8_t), blocksize, memory_card_rawfile) == blocksize)
    {
        // Check if we have found the beginning of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If a previous JPEG file was already opened, close it
            if (jpeg_detected == 1)
            {
                fclose(jpeg_img);
            }
            else
            {
                // Mark that we have found the first JPEG
                jpeg_detected = 1;
            }

            // Create and name a new file for the JPEG
            sprintf(jpeg_name, "%03i.jpg", count_file);
            jpeg_img = fopen(jpeg_name, "w");
            if (jpeg_img == NULL)
            {
                printf("Could not create image file.\n");
                // Free the buffer memory before returning
                free(buffer);
                fclose(memory_card_rawfile);
                return 1;
            }
             // Increment the JPEG file counter
            count_file++;
        }

        // If a JPEG has been found, keep writing to the file
        if (jpeg_detected == 1)
        {
            fwrite(buffer, sizeof(uint8_t), blocksize, jpeg_img);
        }
    }

    // Close any remaining open files
    if (jpeg_img != NULL)
    {
        fclose(jpeg_img);
    }

    // Free the dynamically allocated buffer memory
    free(buffer);

    fclose(memory_card_rawfile);
    return 0;
}
