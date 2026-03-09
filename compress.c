#include <stdio.h>

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

int main(int argc, char* argv[])
{
	if(argc <= 1) { printf("Invalid arguments.\n"); return 1; }
	else
	{
		/* Load first file */
		fptr1 = fopen(argv[1], "rb");
		if(fptr1 == NULL) { printf("Cannon open file.\n"); return 1; }

		/* Load second file */
//		fptr2 = fopen(argv[2], "w");
//		if(fptr2 == NULL) { printf("Cannon open file.\n"); return 1; }
        
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
}
