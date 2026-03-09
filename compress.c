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
    
    return si;
}

int main(int argc, char* argv[])
{
	if(argc <= 1) { printf("Invalid arguments.\n"); return 1; }
	else
	{
		/* Load first file */
		fptr1 = fopen(argv[1], "r");
		if(fptr1 == NULL) { printf("Cannon open file.\n"); return 1; }

		/* Load second file */
//		fptr2 = fopen(argv[2], "w");
//		if(fptr2 == NULL) { printf("Cannon open file.\n"); return 1; }
        
        long int file_size = getSize(fptr1);
        printf("File size: %ld bytes.\n", file_size);

		/* Loop though file data */
//        while (fgets(buffer, sizeof(buffer), fptr1))
//        {
//            printf("%s", buffer);
//        }

		/* Close files and exit */
		fclose(fptr1);
		//fclose(fptr2);
		return 0;
	}
}
