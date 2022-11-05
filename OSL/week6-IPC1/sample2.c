#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd[2], n;
    char *temp = "Character read from parent is: ";
    pid_t cpid;
    char buf;

    if (argc != 2)
    {
        printf("Insufficient arguements.\n");
        exit(0);
    }

    pipe(fd);

    cpid = fork();

    if (!cpid)
    {
        // child process
        close(fd[1]); // as child won't write anything into the pipe
        write(STDOUT_FILENO, temp, strlen(temp));
        while ((n = read(fd[0], &buf, 1))) // reading char written by parent into the pipe
            write(STDOUT_FILENO, &buf, 1);
        write(STDOUT_FILENO, "\n", 1);
        close(fd[0]);
        exit(0);
    }
    else
    {
        // parent process
        close(fd[0]);                           // as parent won't read anything from the pipe
        write(fd[1], argv[1], strlen(argv[1])); // write input character into the pipe
        close(fd[1]);
        wait(NULL); // wait till child terminates
        exit(0);
    }
    return 0;
}