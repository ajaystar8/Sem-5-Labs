#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fa; 
    char ca;
    char buffer[100] = {0};

    fa = fopen("rf1.txt", "r");
    if(fa == NULL){
        printf("File dosen't exist.\n");
        exit(0);
    }

    int i = 0;
    ca = fgetc(fa);
    while(ca != EOF){
        i = 0; 
        if(ca == '='){
            buffer[i++] = '=';
            ca = fgetc(fa);
            if(ca == '='){
                buffer[i++] = '=';
                buffer[i] = '\0';
                printf("Relational Operator: %s\n", buffer);
            }
            else{
                buffer[i] = '\0';
                printf("Assignment operator: %s\n", buffer);
            }
        }
        else if(ca == '<' || ca == '>' || ca == '!'){
            buffer[i++] = ca; 
            ca = fgetc(fa);
            if(ca == '='){
                buffer[i++] = ca;
                buffer[i] = '\0';
            }
            printf("Relational Operator: %s\n", buffer);
        }
        else if(ca == '+' || ca == '-' || ca == '*' || ca == '/'){
            printf("Arithmetic Operator: %c\n", ca);
        }
        ca = fgetc(fa);
    }
    return 0; 
}