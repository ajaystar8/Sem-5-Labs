#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *fa, *fb;
    char ca, cb;
    char buffer[100];
    int i = 0;

    fa = fopen("q2in.txt", "r");
    if (fa == NULL)
    {
        printf("File doesn't exist.\n");
        exit(0);
    }

    fb = fopen("q2out.txt", "w");

    ca = getc(fa);

    while (ca != EOF)
    {
        if (ca == '#')
        {
            while (ca != '\n')
                ca = getc(fa);
        }
        else
            break;
        ca = getc(fa);
    }

    while (ca != EOF)
    {
        putc(ca, fb);
        ca = getc(fa);
    }

    fclose(fa);
    return 0;
}
