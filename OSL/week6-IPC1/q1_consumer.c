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
    int fd, res, n;
    char numString[1024] = {0};

    printf("CONSUMER PROCESS.\n");

    printf("Opening Consumer process FIFO in O_RDONLY mode.\n");

    fd = open(FIFO_NAME, O_RDONLY);

    if (fd != -1)
    {

        n = read(fd, numString, 1024);
        for (int i = 0; i < 4; i++)
            printf("%c ", numString[i]);
        printf("\n");
        close(fd);
    }
    else
    {
        printf("Failed.\n");
        exit(0);
    }
    printf("Consumer Process finished\n");

    return 0;
}