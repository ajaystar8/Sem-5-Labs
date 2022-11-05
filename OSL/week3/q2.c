#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed.");
        exit(-1);
    }
    else if (pid == 0)
    {
        execlp("./exec1", "./", NULL);
    }

    else
    {
        wait(NULL);
        printf("Child complete.\n");
        exit(0);
    }
}