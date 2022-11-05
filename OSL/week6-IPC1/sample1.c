#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

int main()
{
    int n;
    int fd[2];
    char buff[1024] = {0};
    char *data = "sample string.";
    
    pipe(fd);
    write(fd[1], data, strlen(data));

    if ((n = read(fd[0], buff, 1024)))
    {
        buff[n] = 0;
        printf("String read is: %s\n", buff);
    }
    else
        printf("Can't read.\n");

    return 0;
}