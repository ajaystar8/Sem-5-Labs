#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{

    int fd1, fd2, lineCount = 0, i = 0;
    char ch, answer;
    char line[100];

    fd1 = open(argv[1], O_RDONLY);
    if (fd1 == -1)
    {
        printf("File doesn't exist.\n");
        exit(2);
    }

    while (read(fd1, &ch, 1) > 0)
    {
        if (ch != '\n')
            line[i++] = ch;
        else
        {
            i = 0;
            lineCount++;
            printf("%s\n", line);
            if (lineCount == 20)
            {
                lineCount = 0;
                printf("Do you want to continue? (y/n): ");
                fflush(stdin);
                scanf("%c", &answer);
                if (answer == 'y')
                    continue;
                else
                    exit(0);
            }
        }
    }

    // for the second file
    fd2 = open(argv[2], O_RDONLY);
    if (fd2 == -1)
    {
        printf("File doesn't exist.\n");
        exit(2);
    }

    while (read(fd2, &ch, 1) > 0)
    {
        if (ch != '\n')
            line[i++] = ch;
        else
        {
            lineCount++;
            i = 0;
            printf("%s\n", line);
            if (lineCount == 20)
            {
                lineCount = 0;
                printf("Do you want to continue? (y/n): ");
                fflush(stdin);
                scanf("%c", &answer);
                if (answer == 'y')
                    continue;
                else
                    exit(0);
            }
        }
    }

    return 0;
}