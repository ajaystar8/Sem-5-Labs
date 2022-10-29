#include <stdio.h>
#include <stdlib.h>

int main (){
    FILE *fptr, *fptr2;
    char filename[100], writeFile[100], c;

    printf("Enter the name of the file: ");
    scanf("%s", filename);

    fptr = fopen(filename, "r");

    if(!fptr){
        printf("File does not exist.\n");
        exit(0);
    }

    fseek(fptr, 0L, SEEK_END);

    long int size = ftell(fptr);

    printf("The size of the file is %li bytes. \n", size);

    printf("Enter the filename to write content: ");
    scanf("%s", writeFile);
    fptr2 = fopen(writeFile, "w+");

    fseek(fptr, -2L, SEEK_END);

    while(size){
        c = fgetc(fptr);
        fputc(c, fptr2);
        fseek(fptr, -2L, SEEK_CUR);
        size--;
    }



    fclose(fptr);
    fclose(fptr2);

    return 0; 
}