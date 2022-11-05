#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

FILE *fptr;
char c, buff[100] = {0};
int row = 1, col = 1;

// keywords
char keys[33][10] = {"auto", "break", "case", "char",
                     "const", "continue", "default", "do",
                     "double", "else", "enum", "extern",
                     "float", "for", "goto", "if",
                     "int", "long", "register", "return",
                     "short", "signed", "sizeof", "static",
                     "struct", "switch", "typedef", "union",
                     "unsigned", "while", "volatile", "void", "main"};

char symbol[9][1] = {'$', '[', ']', '(', ')', '{', '}', ',', ';'};

struct token
{
    char tokenName[100];
    int row, col;
};

int findSymbol(char c)
{
    for (int i = 0; i < 9; i++)
        if (symbol[i][0] == c)
            return i;
    return -1;
}

struct token *getNextToken()
{
    struct token *newToken = (struct token *)malloc(sizeof(newToken));
    newToken->row = newToken->col = 0;
    c = fgetc(fptr);
loop:
    // ---------STEP-1--------------
    // 1) Handle EOF
    if (c == EOF)
        return NULL;
    // 2) Handle Spaces/Tabs
    if (c == ' ' || c == '\t')
    {
        while (c == ' ' || c == '\t')
        {
            c = fgetc(fptr);
            col++;
        }
        goto loop;
    }
    // 3) Handle Preprocessor Directives
    if (c == '#')
    {
        while (c != '\n')
        {
            c = fgetc(fptr);
            col++;
        }
        goto loop;
    }
    // 4) Single/MultiLine Comments
    if (c == '/')
    {
        c = fgetc(fptr);
        if (c == '/')
        {
            // single line comment
            while (c != '\n')
            {
                c = fgetc(fptr);
                col++;
            }
            col = 1;
            goto loop;
        }
        else if (c == '*')
        {
        multiline:
            do
            {
                c = fgetc(fptr);
                if (c == '\n')
                    row++;
                col++;
            } while (c != '*');
            c = fgetc(fptr);
            col++;
            if (c == '/')
                c = fgetc(fptr);
            else
                goto multiline;
            goto loop;
        }
    }
    // 5) Newline characters
    if (c == '\n')
    {
        while (c == '\n')
        {
            row++;
            c = fgetc(fptr);
        }
        col = 1;
        goto loop;
    }
    // ---------------STEP-2--------------------
    // 1) Handle alphabets
    if (isalpha(c))
    {
        int i = 0, j = 0;
        newToken->row = row;
        newToken->col = col;
        while (isalpha(c))
        {
            buff[i++] = c;
            c = fgetc(fptr);
            col++;
        }
        buff[i] = '\0';
        fseek(fptr, -1, SEEK_CUR);
        // check if word in buffer is a keyword
        for (j = 0; j < 33; j++)
        {
            if (!strcmp(keys[j], buff))
            {
                strcpy(newToken->tokenName, keys[j]);
                memset(buff, 0, 100);
                return newToken; // check
            }
        }
        if (j == 33)
        {
            // buffer word is an identifier
            strcpy(newToken->tokenName, "id");
            newToken->row = row;
            newToken->col = col;
            memset(buff, 0, 100);
            return newToken; // check
        }
    }
    // 2) Handle Numbers
    if (isdigit(c))
    {
        newToken->row = row;
        newToken->col = col;
        int i = 0;
        while (isdigit(c))
        {
            buff[i++] = c;
            c = fgetc(fptr);
            col++;
        }
        buff[i] = '\0';
        fseek(fptr, -1, SEEK_CUR);
        strcpy(newToken->tokenName, "NUM");
        memset(buff, 0, 100);
        return newToken;
    }
    // 3) Handle Symbols
    if (findSymbol(c) != -1)
    {
        buff[0] = c;
        buff[1] = '\0';
        strcpy(newToken->tokenName, buff);
        newToken->row = row;
        newToken->col = col;
        memset(buff, 0, 100);
        return newToken;
    }
    // 4) Handle String Literals
    if (c == '"')
    {
        newToken->row = row;
        newToken->col = col;
        int i = 0;
        do
        {
            buff[i++] = c;
            c = fgetc(fptr);
            col++;
        } while (c != '"');
        buff[i++] = c;
        buff[i] = '\0';
        strcpy(newToken->tokenName, buff);
        memset(buff, 0, 100);
        return newToken;
    }
    // 5) Handle Operators
    if (c == '+' || c == '-' || c == '*' || c == '/')
    {
        newToken->row = row;
        newToken->col = col;
        int i = 0;
        buff[i++] = c;
        c = fgetc(fptr);
        col++;
        buff[i++] = c;
        buff[i] = '\0';
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=')
        {
            strcpy(newToken->tokenName, buff);
            memset(buff, 0, 100);
            return newToken;
        }
        else
        {
            buff[i - 1] = '\0';
            fseek(fptr, -1, SEEK_CUR);
            strcpy(newToken->tokenName, buff);
            memset(buff, 0, 100);
            return newToken;
        }
    }
    if (c == '>' || c == '<' || c == '=')
    {
        newToken->row = row;
        newToken->col = col;
        int i = 0;
        buff[i++] = c;
        c = fgetc(fptr);
        col++;
        buff[i++] = c;
        buff[i] = '\0';
        if (c == '=')
        {
            strcpy(newToken->tokenName, buff);
            memset(buff, 0, 100);
            return newToken;
        }
        else
        {
            buff[i - 1] = '\0';
            fseek(fptr, -1, SEEK_CUR);
            strcpy(newToken->tokenName, buff);
            memset(buff, 0, 100);
            return newToken;
        }
    }
    return newToken;
}

int main()
{
    fptr = fopen("ip.txt", "r");
    struct token *newToken = (struct token *)malloc(sizeof(struct token));

    while (1)
    {
        newToken = getNextToken();
        if (!newToken)
            break;
        printf("<%s, %d, %d>\n", newToken->tokenName, newToken->row, newToken->col);
    }

    return 0;
}