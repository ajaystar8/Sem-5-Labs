#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{

    printf("Process ID is: %d\n", getpid());

    int status;
    pid_t pid;
    pid = fork();

    if (pid == -1)
        printf("\nERROR child not created");
    else if (pid == 0)
    {
        printf("\nI'm the child!\n");
        printf("C-My process ID is: %d\n", getpid());
        printf("C-ID returned by fork to child: %d\n", pid);
        printf("C-My parent ID is: %d\n", getppid());
        exit(0);
    }
    wait(NULL);
    printf("P-I'm the parent.\n");
    printf("P-My process ID is: %d\n", getpid());
    printf("P-ID returned by fork to parent->process id of child: %d\n", pid);
    printf("P-My parent ID is: %d\n", getppid());
    
    return 0; 
}
