#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

FILE *fa, *fb;
char ca, cb;
char buff[100] = {0};
int i = 0;

struct token
{
    char tokenName[100];
    char returnType[100];
    int size;
    char type[100];
};

char keys[32][10] = {"auto", "break", "case", "char",
                     "const", "continue", "default", "do",
                     "double", "else", "enum", "extern",
                     "float", "for", "goto", "if",
                     "int", "long", "register", "return",
                     "short", "signed", "sizeof", "static",
                     "struct", "switch", "typedef", "union",
                     "unsigned", "while", "volatile", "void"};

char symbol[8][1] = {'[', ']', '(', ')', '{', '}', ',', ';'};

void preprocessFile()
{
    ca = fgetc(fa);
    while (ca != EOF)
    {
        // blank spaces
        if (ca == ' ')
        {
            putc(ca, fb);
            while (ca == ' ')
                ca = getc(fa);
        }

        // preprocessor directives
        if (ca == '#')
        {
            while (ca == '#')
            {
                while (ca != '\n')
                    ca = getc(fa);
                ca = getc(fa);
            }
            fseek(fa, -1, SEEK_CUR);
        }

        else
            putc(ca, fb);

        ca = getc(fa);
    }
    fclose(fa);
}

struct token *getNextToken()
{
    struct token *newToken = (struct token *)malloc(sizeof(struct token));

    cb = getc(fb);

    while (cb != EOF)
    {
        i = 0;
        if (cb == ' ')
            continue;

        // generate lexeme
        while (isalpha(cb))
        {
            buff[i++] = cb;
            cb = fgetc(fb);
        }
        buff[i] = '\0';

        // if lexeme is a keyword
        int j;
        for (j = 0; j < 32; j++)
        {
            if (!strcmp(keys[j], buff))
            {
                // yes, its a keyword
                strcpy(newToken->tokenName, buff);
                strcpy(newToken->returnType, "keyword");
                newToken->size = sizeof(keys[j]);
                strcpy(newToken->type, "keyword");
                return newToken;
            }
        }
        if (j == 32)
        {
            strcpy(newToken->tokenName, buff);
            strcpy(newToken->returnType, "id");
            newToken->size = sizeof(buff);
            strcpy(newToken->type, "id");
            return newToken;
        }
        cb = getc(fb);

        // if lexeme is a symbol
        j = 0;
        for (j = 0; j < 8; j++)
        {
            if (!strcmp(symbol[j], buff))
            {
                strcpy(newToken->tokenName, "symbol");
                strcpy(newToken->returnType, "symbol");
                newToken->size = sizeof(buff);
                strcpy(newToken->type, "symbol");
                return newToken;
            }
        }
        if (j == 8)
        {
            return NULL;
        }
        else
            return NULL;
    }
}

int main()
{

    fa = fopen("rf1.txt", "r");

    fb = fopen("wf1.txt", "w+");

    preprocessFile();

    // work on fb

    fseek(fb, 0, SEEK_SET);

    cb = fgetc(fb);

    while (cb != EOF)
    {
        // printf("%c\n", cb);
        struct token *temp = getNextToken();
        printf("<%s, %s, %d, %s>\n", temp->tokenName, temp->returnType, temp->size, temp->type);
    }

    return 0;
}