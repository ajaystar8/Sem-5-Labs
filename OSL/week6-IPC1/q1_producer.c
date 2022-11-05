#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "my_pipe"

int main()
{
    int fd, res;
    char numString[1024] = {0};

    if (access(FIFO_NAME, F_OK) == -1)
    {
        res = mkfifo(FIFO_NAME, 0777);
        if (res)
        {
            printf("FIFO creation failed.\n");
            exit(0);
        }
    }

    printf("PRODUCER PROCESS.\n");

    fd = open(FIFO_NAME, O_WRONLY);

    printf("Opening Producer process FIFO in O_WRONLY mode.\n");

    if (fd != -1)
    {
        printf("Enter 4 integers: \n");
        for (int i = 0; i < 4; i++)
        {
            scanf("%c", &numString[i]);
            fflush(stdin);
        }
        write(fd, numString, sizeof(numString));
        close(fd);
        printf("Integers written successfully.\n");
    }
    else
    {
        printf("Failure.\n");
        exit(0);
    }

    printf("Producer process completed.\n");

    return 0;
}