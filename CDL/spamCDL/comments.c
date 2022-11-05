#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

int main(){

    FILE *fptr1, *fptr2;
    char c1, c2; 

    fptr1 = fopen("read.txt", "r");
    fptr2 = fopen("write.txt", "w+");
    c1 = getc(fptr1);

    while(c1 != EOF){
        if( c1 == '/'){
            c2 = fgetc(fptr1);
            if(c2 == '/'){
                //confirmed multi line comment
                while(c2 != '\n')
                    c2 = fgetc(fptr1);
                fputc(c2, fptr2);
            }
            else if(c2 == '*'){
                //confirmed multi line comment
                c2 = fgetc(fptr1);
                while(c2 != '*'){
                    c2 = fgetc(fptr1);
                    if(c2 == '\n')
                        fputc(c2, fptr2);
                    if(c2 == '*'){
                        //check next character if it is a '/'
                        c2 = fgetc(fptr1);
                        if(c2 == '/')
                            break; 
                        else
                            continue;
                    }
                }
            }
        }
        else
            fputc(c1, fptr2);
        c1 = fgetc(fptr1);
    }


    return 0; 
}