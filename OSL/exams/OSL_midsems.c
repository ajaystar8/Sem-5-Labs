#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    char input1[200], input2[100];
    int input3;
    int fd, stat = 1;
    char c, ch;

    printf("Enter contents of file: ");
    fgets(input1, 200, stdin);
    printf("Enter file name: ");
    scanf("%s", input2);
    printf("Enter from where to start: ");
    scanf("%d", &input3);

    fd = open(input2, O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR);

    int len = strlen(input1);
    int start=0; 

    while(input3){
        start++;
        input3--;
    }

    for(int i = start; i < len; i++)
        if(input1[i] == ' ')
            input1[i+1] = '%'; 

    for(int i = 0; i < strlen(input1); i++)
        write(fd, &input1[i], 1);

    close(fd);

    fd = open(input2, O_RDONLY);

    while(read(fd, &c, 1) > 0)
        printf("%c", c);

    return 0; 
}
