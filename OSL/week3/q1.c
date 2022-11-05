#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int status;
    pid_t pid;
    pid = fork();

    if (pid == -1)
        printf("\n ERROR child not created");
    else if (pid == 0)
    {
        printf("\n I'm the child!\n");
        exit(0);
    }
    else
    {
        printf("\n I'm the parent!");
        wait(&status);
        printf("\n Child returned: %d\n", status);
    }
    return 0;
}
