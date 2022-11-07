#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char keys[33][10] = {"auto", "break", "case", "char",
                     "const", "continue", "default", "do",
                     "double", "else", "enum", "extern",
                     "float", "for", "goto", "if",
                     "int", "long", "register", "return",
                     "short", "signed", "sizeof", "static",
                     "struct", "switch", "typedef", "union",
                     "unsigned", "while", "volatile", "void", "main"};

char symbol[9][1] = {'$', ':', ']', '(', ')', '{', '}', ',', ';'};

int findSymbol(char c)
{
    for (int i = 0; i < 9; i++)
        if (symbol[i][0] == c)
            return i;
    return -1;
}

FILE *fptr;
char c, buff[100] = {0};
int row = 1, col = 1;

struct token
{
    char lexemeName[100];
    int row, col;
};

struct token *getNextToken(FILE *fptr)
{
    struct token *newToken = (struct token *)malloc(sizeof(struct token));
    c = fgetc(fptr);
loop:
    if (c == EOF)
        return NULL;
    if (c == ' ' || c == '\t')
    {
        while (c == ' ' || c == '\t')
        {
            col++;
            c = fgetc(fptr);
        }
        col--;
        goto loop;
    }
    if (c == '#')
    {
        while (c != '\n')
        {
            col++;
            c = fgetc(fptr);
        }
        goto loop;
    }
    if (c == '/')
    {
        c = fgetc(fptr);
        col++;
        if (c == '/')
        {
            while (c != '\n')
            {
                c = fgetc(fptr);
                col++;
            }
            goto loop;
        }
        else if (c == '*')
        {
        multiline:
            do
            {
                c = fgetc(fptr);
                col++;
                if (c == '\n')
                {
                    row++;
                    col = 1;
                }
            } while (c != '*');
            c = fgetc(fptr);
            col++;
            if (c == '/')
            {
                c = fgetc(fptr);
                goto loop;
            }
            else
                goto multiline;
        }
    }
    if (c == '\n')
    {
        while (c == '\n')
        {
            c = fgetc(fptr);
            row++;
        }
        col = 1;
        goto loop;
    }
    if (isalpha(c))
    {
        newToken->row = row;
        newToken->col = col;
        int i = 0, j = 0;
        while (isalnum(c) || c == '_')
        {
            buff[i++] = c;
            c = fgetc(fptr);
            col++;
        }
        buff[i] = '\0';
        fseek(fptr, -1, SEEK_CUR);
        col--;
        for (j = 0; j < 33; j++)
        {
            if (!strcmp(keys[j], buff))
            {
                strcpy(newToken->lexemeName, buff);
                memset(buff, 0, 100);
                break;
            }
        }
        if (j == 33)
        {
            strcpy(newToken->lexemeName, "ID");
            memset(buff, 0, 100);
        }
    }
    else if (isdigit(c))
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
        col--;
        strcpy(newToken->lexemeName, "NUM");
        memset(buff, 0, 100);
    }
    else if (findSymbol(c) != -1)
    {
        newToken->row = row;
        newToken->col = col;
        buff[0] = c;
        buff[1] = '\0';
        strcpy(newToken->lexemeName, buff);
        memset(buff, 0, 100);
    }
    else if (c == '"')
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
        strcpy(newToken->lexemeName, buff);
        memset(buff, 0, 100);
    }
    else if (c == '=' || c == '>' || c == '<' || c == '!')
    {
        newToken->row = row;
        newToken->col = col;
        int i = 0;
        buff[i++] = c;
        c = fgetc(fptr);
        if (c != '=')
        {
            buff[i] = '\0';
            strcpy(newToken->lexemeName, buff);
            fseek(fptr, -1, SEEK_CUR);
        }
        else
        {
            buff[i++] = c;
            buff[i] = '\0';
            strcpy(newToken->lexemeName, buff);
        }
        memset(buff, 0, 100);
    }
    else if (c == '+')
    {
        newToken->row = row;
        newToken->col = col;
        int i = 0;
        buff[i++] = c;
        c = fgetc(fptr);
        if (c == '+' || c == '=')
        {
            buff[i++] = c;
            buff[i] = '\0';
            strcpy(newToken->lexemeName, buff);
        }
        else
        {
            buff[i] = '\0';
            strcpy(newToken->lexemeName, buff);
            fseek(fptr, -1, SEEK_CUR);
        }
        memset(buff, 0, 100);
    }
    else if (c == '-')
    {
        newToken->row = row;
        newToken->col = col;
        int i = 0;
        buff[i++] = c;
        c = fgetc(fptr);
        if (c == '-' || c == '=')
        {
            buff[i++] = c;
            buff[i] = '\0';
            strcpy(newToken->lexemeName, buff);
        }
        else
        {
            buff[i] = '\0';
            strcpy(newToken->lexemeName, buff);
            fseek(fptr, -1, SEEK_CUR);
        }
        memset(buff, 0, 100);
    }
    else if (c == '*' || c == '/')
    {
        newToken->row = row;
        newToken->col = col;
        int i = 0;
        buff[i++] = c;
        c = fgetc(fptr);
        if (c == '=')
        {
            buff[i++] = c;
            buff[i] = '\0';
            strcpy(newToken->lexemeName, buff);
        }
        else
        {
            buff[i] = '\0';
            strcpy(newToken->lexemeName, buff);
            fseek(fptr, -1, SEEK_CUR);
        }
        memset(buff, 0, 100);
    }
    return newToken;
}

// int main()
// {
//     fptr = fopen("ip.txt", "r");
//     struct token *newToken = (struct token *)malloc(sizeof(struct token));
//     while (1)
//     {
//         newToken = getNextToken(fptr);
//         if (!newToken)
//             break;
//         printf("< %s, %d, %d >\n", newToken->lexemeName, newToken->row, newToken->col);
//     }
//     return 0;
// }