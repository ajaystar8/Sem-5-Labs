#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){

    struct stat mystat; 
    int output = stat(argv[1], &mystat);
    if(output == -1){
        printf("Process failed.\n");
        exit(0);
    }

    printf("The inode number of the given file is: %ld\n", mystat.st_ino);
}