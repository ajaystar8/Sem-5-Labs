#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

#define FIFO_NAME "q2_fifo"

int main()
{
    int fd, res;
    char str[1024] = "My name is Ajay.";

    if (access(FIFO_NAME, F_OK) == -1)
    {
        res = mkfifo(FIFO_NAME, 0777);
        if (res)
        {
            printf("FIFO creation failed.\n");
            exit(0);
        }
    }

    while (1)
    {
        // writing to FIFO
        printf("Enter text string to be written for Program 1: ");
        fgets(str, 1024, stdin);
        fd = open(FIFO_NAME, O_WRONLY);
        res = write(fd, str, sizeof(str));
        close(fd);
        // reading from FIFO
        printf("\nProgram 2 reading text written by Program 1: \n");
        fd = open(FIFO_NAME, O_RDONLY);
        if (fd != -1)
        {
            res = read(fd, str, 1024);
            printf("Text read is: %s\n", str);
        }
        close(fd);
    }

    return 0;
}