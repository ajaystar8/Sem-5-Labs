#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main(){
    int status; 
    pid_t pid;
    pid = fork();
    
    if(pid == -1)
        printf("\n ERROR child not created");
    else if(pid == 0){
        printf("\n I'm the child!\n");
        printf("Parent ID before becoming orphan: %d\n", getppid());
        sleep(2);
        printf("Parent ID after becoming orphan: %d\n", getppid());
        exit(0);
    }
    else{
        printf("\n I'm the parent!");
        printf("\n Child returned: %d\n", status);
    }
}

