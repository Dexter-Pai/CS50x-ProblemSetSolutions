#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

// #define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    const int BLOCK_SIZE = 512;
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // if (argv[1] == NULL)
    // {
    //     return 1;
    // }
    FILE * file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }
    FILE * sav = NULL;
    BYTE buffer[BLOCK_SIZE];
    int counter = 0;
    char file_name[8]; // to account for '\0' 7 characters but one for NUL
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE)
    {


        // fread(buffer, sizeof(BYTE), BLOCK_SIZE, file);

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter == 0)
            {
                sprintf(file_name, "%03i.jpg", counter);
                sav = fopen(file_name, "w");
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, sav);
                counter++;

            }
            // else if (counter <10)
            // {
            //     // sprintf(file_name, "00%i.jpg", counter);
            //     fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, sav);
            // }
            // else if (counter <100 && counter >=10)
            // {
            //     // sprintf(file_name, "0%i.jpg", counter);
            //     // sav = fopen(file_name, "w");
            //     fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, sav);
            //     // counter++;
            //     // fclose(sav);
            // }
            else if (counter > 0)
            {
                fclose(sav);
                sprintf(file_name, "%03i.jpg", counter);
                sav = fopen(file_name, "w");
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, sav);
                counter++;
                // fclose(sav);
            }

            // if (counter > 0)
            // {
            //     fclose(sav);
            // }
            // fclose(sav);
            // for (int i = 0; i < BLOCK_SIZE; i++)
            // {
            //     // printf("%i",buffer[i]);
            //     // fwrite(&buffer[i], sizeof(BYTE), sizeof(BYTE), sav);
            //
            // }
            // printf("\n");
            // fputc('\n',sav);
        }
        else if (counter > 0)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, sav);
        }
        // else if (counter > 0)
        // {
        //     fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, sav);
        // }
    }
    fclose(file);
    fclose(sav);
    // free(BLOCK_SIZE);
    // free(file_name);
    return 0;
}

//  {
//     for (int i = 0; i < 512; i++)
//  {
//     printf("%i",buffer[i]);
//  }
//  }
//  printf ("\n");
//  fread(buffer, sizeof(BYTE), 512, file);
//  {
//     for (int i = 0; i < 512; i++)
//  {
//     printf("%i",buffer[i]);
//  }
//  }
//  printf ("\n");
//  fread(buffer, sizeof(BYTE), 512, file);
//  {
//     for (int i = 0; i < 512; i++)
//  {
//     printf("%i",buffer[i]);
//  }
//  }
//  printf ("\n");
//  fread(buffer, sizeof(BYTE), 512, file);
//  {
//     for (int i = 0; i < 512; i++)
//  {
//     printf("%i",buffer[i]);
//  }
//  }
//  for (int i = 0; i < 512; i++)
//  {
//     printf("%i",buffer[i]);
//  }

// }