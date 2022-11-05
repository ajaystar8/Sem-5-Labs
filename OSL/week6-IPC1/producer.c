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
    int open_mode = O_WRONLY;
    char buff[1024] = "I'm produced by the PRODUCER process.";

    if (access(FIFO_NAME, F_OK) == -1)
    {
        res = mkfifo(FIFO_NAME, 0777);
        if (res)
        {
            printf("Failure.\n");
            exit(0);
        }
    }

    printf("PRODUCER PROCESS.\n");

    printf("Process %d opening FIFO in O_WRONLY mode.\n", getpid());

    fd = open(FIFO_NAME, open_mode);
    if (fd != -1)
    {
        res = write(fd, buff, strlen(buff));
        close(fd);
    }
    else
        exit(0);
    printf("Content written into FIFO file is: %s\n", buff);
    printf("Producer Process %d finished\n", getpid());
    exit(0);

    return 0;
}