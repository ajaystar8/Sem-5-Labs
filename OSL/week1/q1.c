#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int fd, i = 0, k = 0;
    char line[100];
    char c;

    if (argc != 3)
    {
        printf("\nInsufficient Arguments\n");
        exit(1);
    }

    fd = open(argv[2], O_RDONLY);
    if (fd == -1)
    {
        printf("File doesn't exist.\n");
        exit(2);
    }

    while (read(fd, &c, 1) > 0)
    {
        if (c != '\n')
            line[i++] = c;
        else
        {
            k++;
            line[i] = '\0';
            i = 0;
            if (strstr(line, argv[1]) != NULL)
                printf("Line : %d\t %s\n", k, line);
        }
    }

    return 0;
}