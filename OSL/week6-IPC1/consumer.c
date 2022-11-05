#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "/tmp/newfifo"

int main()
{
    int fd, res;
    int open_mode = O_RDONLY;
    char buff[1024] = {0};

    printf("CONSUMER PROCESS.\n");

    printf("Process %d opening FIFO in O_RDONLY mode.\n", getpid());
    fd = open(FIFO_NAME, open_mode);

    if (fd != -1)
    {
        do
        {
            res = read(fd, buff, 1024);
        } while (res > 0);
        close(fd);
    }
    else
        exit(0);
    printf("Content read from FIFO file is: %s\n", buff);
    printf("Consumer Process %d finished\n", getpid());
    return 0;
}