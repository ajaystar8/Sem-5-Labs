#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *fa, *fb;
    char ca, cb;
    char buffer[100];
    char keywords[11][100] = {"int", "main", "char",
                              "FILE", "while", "if",
                              "else if", "else", "continue",
                              "break", "return"};
    int i = 0;

    fa = fopen("q3in.txt", "r");
    if (fa == NULL)
    {
        printf("File doesn't exist.\n");
        exit(0);
    }

    fb = fopen("q3out.txt", "w");

    ca = getc(fa);

    // check for keywords
    while (ca != EOF)
    {
        while (isalpha(ca))
        {
            buffer[i++] = ca;
            ca = getc(fa);
        }
        buffer[i] = '\0';
        for (int i = 0; i < 11; i++)
        {
            if (strcmp(buffer, keywords[i]) == 0)
            {
                for (int j = 0; j < strlen(buffer); j++)
                    putc(toupper(buffer[j]), fb);
                putc('\n', fb);
                break;
            }
        }
        memset(buffer, 0, 100);
        i = 0;
        ca = getc(fa);
    }
    printf("Process completed successfully. \n");

    return 0;
}
