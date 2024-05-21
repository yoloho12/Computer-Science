#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    char *file = argv[1];
    FILE *in_ptr = NULL;
    FILE *out_ptr = NULL;
    char dynamic_name[8];
    int dynamic_val = 0;
    // typedef uint8_t BYTE
    BYTE buffer[512];
    
    if (argc == 2)
    {
        file = argv[1];
    }
    else
    {
        printf("Usage: ./recover image");
        return 1;
    }

    in_ptr = fopen(file, "r");

    //open input file
    if (in_ptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", file);
        return 1;
    }

    while (1)
    {
        int bytes = fread(buffer, sizeof(BYTE), 512, in_ptr);

        if (bytes == 0 && feof(in_ptr))
        {
            break;
        }
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] == 0xe0 || buffer[3] == 0xe1 || buffer [3] == 0xe2 ||
             buffer[3] == 0xe3 || buffer[3] == 0xe4 || buffer [3] == 0xe5 ||
             buffer[3] == 0xe6 || buffer[3] == 0xe7 || buffer [3] == 0xe8 ||
             buffer[3] == 0xe9 || buffer[3] == 0xea || buffer [3] == 0xeb ||
             buffer[3] == 0xec || buffer[3] == 0xed || buffer [3] == 0xee || buffer [3] == 0xef) && out_ptr != NULL)
        {
            fclose(out_ptr);
        }   
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] == 0xe0 || buffer[3] == 0xe1 || buffer [3] == 0xe2 ||
             buffer[3] == 0xe3 || buffer[3] == 0xe4 || buffer [3] == 0xe5 ||
             buffer[3] == 0xe6 || buffer[3] == 0xe7 || buffer [3] == 0xe8 ||
             buffer[3] == 0xe9 || buffer[3] == 0xea || buffer [3] == 0xeb ||
             buffer[3] == 0xec || buffer[3] == 0xed || buffer [3] == 0xee || buffer [3] == 0xef))
        {
            sprintf(dynamic_name, "%03i.jpg", dynamic_val);
            out_ptr = fopen(dynamic_name, "w");
            dynamic_val++;
        }
        if (out_ptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), bytes, out_ptr);
        }

    }
    fclose(out_ptr);
    fclose(in_ptr);
    return 0;
}
