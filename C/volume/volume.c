// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    // int16_t factor_converted = atof(argv[3]);
    // TODO: Copy header from input file to output file
    uint8_t *header = malloc(HEADER_SIZE);
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // TODO: Read samples from input file and write updated data to output file
    int16_t body;
    while (fread(&body, sizeof(int16_t), 1, input))
    {
        // while ((body = fgetc(input)) != EOF)
        // {
        body *= factor;
        fwrite(&body, sizeof(int16_t), 1, output);
    }

    // fputc(body, output);
    // }
    // for (int i = 0; body[i] != '\0'; i++)
    // {
    //     body[i] = body[i] * factor_converted;
    //     fwrite(&body[i], 1, sizeof(int16_t), output);
    // }
    // Close files
    free(header);
    fclose(input);
    fclose(output);
}
