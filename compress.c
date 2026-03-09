#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* TODO
 * Implement file loading form argument
 * Load file data
 * Save file data
 */

FILE *fptr1, *fptr2;
int c;

/* Get file size */
long int getSize(FILE *fp)
{
    fseek(fp, 0L, SEEK_END);
    if(fp == NULL) { return 1; }

    long int si = ftell(fp);
   
    /* Rewind is very important for other functions */
    rewind(fp);
    return si;
}

/* https://dev.to/farhadrahimiklie/building-a-file-compressor-in-c-from-scratch-2n25 */
int compress_file(const char *input_file, const char *output_file)
{
    FILE *in = fopen(input_file, "rb");
    if(!in) { perror("Input file error"); return 1; }

    FILE *out = fopen(output_file, "wb");
    if(!out) { perror("Ouput file error"); fclose(in); return 1; }
    
    /* Get the character and store it in prev */
    int prev = fgetc(in);
    if(prev == EOF) { fclose(in); fclose(out); return 0; }

    int count = 1;
    int current;

    while((current = fgetc(in)) != EOF)
    {
        if(current == prev) { count++; }
        else
        {
            /* Do the funky char count code here 
             * Do a check if the char count is > 2
             * becuase it will just return a filesize
             * the same as the original. */
            if(count > 2)
                fprintf(out, "%c%d", prev, count);
            else
                fprintf(out, "%c", prev);

            prev = current;
            count = 1;
        }
    }

    fprintf(out, "%c%d", prev, count);

    fclose(in);
    fclose(out);
    return 0;
}

int decompress_file(const char *input_file, const char *output_file)
{
    FILE *in = fopen(input_file, "rb");
    if(!in) { perror("Input file error"); return 1; }

    FILE *out = fopen(output_file, "wb");
    if(!out) { perror("Ouput file error"); fclose(in); return 1; }

    int ch;
    while((ch = fgetc(in)) != EOF)
    {
        int count = 0;
        int digit;

        while((digit = fgetc(in)) != EOF && isdigit(digit))
        {
            count = count * 10 + (digit - '0');
        }
        
        for(int i = 0; i < count; i++)
        {
            fputc(ch, out);
        }

        if(digit != EOF) { ungetc(digit, in); }
    }

    fclose(in);
    fclose(out);
    return 0;
}

int main(int argc, char* argv[])
{
	if(argc <= 1) { printf("Invalid arguments.\n"); return 1; }

    if(strcmp(argv[1], "-c") == 0) { return compress_file(argv[2], argv[3]); }
    else if(strcmp(argv[1], "-d") == 0) { return decompress_file(argv[2], argv[3]); }

    printf("Unknown argument.\n");

    /* Load first file */
    fptr1 = fopen(argv[1], "rb");
    if(fptr1 == NULL) { printf("Cannon open file.\n"); return 1; }

    long int file_size = getSize(fptr1);
    printf("File size: %ld bytes.\n", file_size);

    char buffer[file_size];
    int byte;
    int count = 0;

    /* Loop though file data */
    while ((byte = fgetc(fptr1)) != EOF)
    {
        printf("%02X ", byte);
        count++;

        if(count % 16 == 0) { printf("\n"); }

        printf("%s", buffer);
    }

    /* Close files and exit */
    fclose(fptr1);
    //fclose(fptr2);
    return 0;
}
