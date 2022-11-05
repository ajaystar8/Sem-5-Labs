#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
    int status;
    pid_t pid;
    pid = fork();

    if (pid == -1)
        printf("\n ERROR child not created");
    else if (pid == 0)
    {
        printf("I'm a child zombie!\n");
        exit(0);
    }
    else
    {
        printf("I'm the parent!\n");
        sleep(5);
        printf("Dead Child returned: %d\n", status);
    }
}
