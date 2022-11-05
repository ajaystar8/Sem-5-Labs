#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fptr1, *fptr2, *fptr3;
    char readFile1[100], readFile2[100], writeFile[100], c1, c2;
    int flag; 

    printf("Enter the name of the 1st file: ");
    scanf("%s", readFile1);

    fptr1 = fopen(readFile1, "r");

    if(!fptr1){
        printf("File does not exist.\n");
        exit(0);
    }

    printf("Enter the name of the 2nd file: ");
    scanf("%s", readFile2);

    fptr2 = fopen(readFile2, "r");

    if(!fptr2){
        printf("File does not exist.\n");
        exit(0);
    }

    printf("Enter the name of the new file: ");
    scanf("%s", writeFile);

    fptr3 = fopen(writeFile, "w+");

    c1 = getc(fptr1);
    c2 = getc(fptr2);

    while(c1 != EOF || c2 != EOF){
        while(c1 != '\n' && c1 != EOF){
            fputc(c1, fptr3);
            c1 = getc(fptr1);
        }
        if(c1 == '\n'){
            fputc('\n', fptr3);
            c1 = getc(fptr1);
        }
        while(c2 != '\n' && c2 != EOF){
            fputc(c2, fptr3);
            c2 = getc(fptr2);
        }
        if(c2 == '\n'){
            fputc('\n', fptr3);
            c2 = getc(fptr2);
        }
    }

    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);

    return 0; 
}
