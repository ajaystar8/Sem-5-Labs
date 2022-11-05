#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int input_fd, output_fd;
    char inputFile[100], outputFile[100];
    char c;

    printf("Enter the source text file name: ");
    scanf("%s", inputFile);

    input_fd = open(inputFile, O_RDONLY);
    if (input_fd == -1)
    {
        printf("File doesn't exist.\n");
        exit(2);
    }

    printf("Enter the destination text file name: ");
    scanf("%s", outputFile);

    output_fd = open(outputFile, O_RDWR);
    if (output_fd == -1)
    {
        printf("File doesn't exist.\n");
        exit(2);
    }
    while (read(input_fd, &c, 1) > 0)
        write(output_fd, &c, 1);

    printf("Process successful.\n");

    return 0;
}