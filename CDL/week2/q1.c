#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fa, *fb;
    char ca, cb;

    fa = fopen("q1in.txt", "r");
    if (fa == NULL)
    {
        printf("File doesn't exist.\n");
        exit(0);
    }

    fb = fopen("q1out.txt", "w");

    ca = getc(fa);

    while (ca != EOF)
    {
        if (ca == ' ')
        {
            putc(ca, fb);
            while (ca == ' ')
                ca = getc(fa);
        }
        else if (ca == '\t')
        {
            putc(' ', fb);
            while (ca == '\t')
                ca = getc(fa);
        }
        putc(ca, fb);
        ca = getc(fa);
    }

    return 0;
}
