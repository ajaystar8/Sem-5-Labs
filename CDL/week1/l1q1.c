#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fptr;
    char filename[100], c;
    int charCount = 0;
    int lineCount = 0;

    printf("Enter the name of the file: ");
    scanf("%s", filename);

    fptr = fopen(filename, "r");

    if(!fptr){
        printf("File does not exist.\n");
        exit(0);
    }

    c = fgetc(fptr);

    while(c != EOF){
        if(c != ' ' && c != '\n' || c != '\t')
            charCount++;
        if(c == '\n' || c == '\0')
            lineCount++;
        c = fgetc(fptr);
    }

    printf("The number of characters are: %d\n", charCount);
    printf("The number of lines are: %d\n", lineCount);

    fclose(fptr);

    return 0; 
}