#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int main(){
    FILE *fptr1, *fptr2;
    char c; 

    fptr1 = fopen("read.txt", "r");
    fptr2 = fopen("write.txt", "w+");
    c = getc(fptr1);

    while(c != EOF){
        if(c == ' ' || c == '\t'){
            fputc(c, fptr2);
            while( c == ' ' || c == '\t'){
                c = fgetc(fptr1);
            }
        }
        else{
            fputc(c, fptr2);
            c = fgetc(fptr1);
        }
    }

    return 0; 
}