#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_TABLE_SIZE 100

char keys[33][10] = {"auto", "break", "case", "char",
                     "const", "continue", "default", "do",
                     "double", "else", "enum", "extern",
                     "float", "for", "goto", "if",
                     "int", "long", "register", "return",
                     "short", "signed", "sizeof", "static",
                     "struct", "switch", "typedef", "union",
                     "unsigned", "while", "volatile", "void", "main"};

char symbol[9][1] = {'$', '[', ']', '(', ')', '{', '}', ',', ';'};

int findSymbol(char c)
{
    for (int i = 0; i < 9; i++)
        if (symbol[i][0] == c)
            return i;
    return -1;
}

struct token
{
    char lexemeName[100];
    int row, col;
};

struct node
{
    char lexemeName[100];
    char type[100];
    int size;
    char returnType[100];
};

struct node SymbolTable[MAX_TABLE_SIZE];
FILE *fptr;
struct node *t;
int idx = 0, row = 1, col = 1, flag = 0, s = 0;
char buff[100] = {0}, dbuff[100] = {0}, size[100] = {0};

int searchSymbolTable(char lexemeName[100])
{
    for (int i = 0; i < idx; i++)
        if (!strcmp(lexemeName, SymbolTable[i].lexemeName))
            return i;
    return -1;
}

void insertSymbolTable(char lexemeName[100], char type[100], int size, char returnType[100])
{
    if (searchSymbolTable(lexemeName) == -1)
    {
        struct node newNode;
        strcpy(newNode.lexemeName, lexemeName);
        strcpy(newNode.type, type);
        newNode.size = size;
        strcpy(newNode.returnType, returnType);
        SymbolTable[idx++] = newNode;
    }
}

void displaySymbolTable()
{
    printf("\n\n-----------SYMBOL TABLE-----------------\n\n");
    printf("LexemeName\t\tType\t\tSize\t\tReturn-Type\n");
    for (int i = 0; i < idx; i++)
        printf("%s\t\t\t%s\t%d\t\t%s\n", SymbolTable[i].lexemeName, SymbolTable[i].type, SymbolTable[i].size, SymbolTable[i].returnType);
}

struct token *getNextToken(FILE *fptr)
{
    struct token *newToken = (struct token *)malloc(sizeof(struct node));
    newToken->row = newToken->col = 0; // change
    char c = fgetc(fptr);
    if (c == EOF)
        return NULL;
loop:
    if (c == ' ' || c == '\t')
    {
        while (c == ' ' || c == '\t')
        {
            c = fgetc(fptr);
            col++;
        }
        goto loop;
    }
    if (c == '#')
    {
        while (c != '\n')
        {
            c = fgetc(fptr);
            col++;
        }
        goto loop;
    }
    if (c == '/')
    {
        c = fgetc(fptr);
        col++;
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
            {
                c = fgetc(fptr);
                // col++;
            }
            else
                goto multiline;
            goto loop;
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
        fseek(fptr, -1, SEEK_CUR);
        col--;
        buff[i] = '\0';
        // check if keyword
        for (j = 0; j < 33; j++)
        {
            if (!strcmp(keys[j], buff))
            {
                strcpy(newToken->lexemeName, buff);
                if (!strcmp(buff, "int") || !strcmp(buff, "float") || !strcmp(buff, "char") || !strcmp(buff, "double") || !strcmp(buff, "void"))
                {
                    flag = 1;
                    strcpy(dbuff, buff);
                }
                memset(buff, 0, 100);
                break;
            }
        }
        if (j == 33)
        {
            // identifier
            if (flag)
            {
                // declaration made
                c = fgetc(fptr);
                col++;
                if (c == '(')
                {
                    // function declaration
                    c = fgetc(fptr);
                    col++;
                    if (isalpha(c) || c == ')')
                        insertSymbolTable(buff, "FUNC", 0, dbuff);
                    fseek(fptr, -2, SEEK_CUR);
                    col -= 2;
                }
                else if (c == '[')
                {
                    // array declaration
                    while (c != ']')
                    {
                        c = fgetc(fptr);
                        col++;
                        if (c != ']')
                            size[s++] = c;
                    }
                    fseek(fptr, -(s + 2), SEEK_CUR);
                    col -= (s + 2);
                    int arrSize = atoi(size);
                    insertSymbolTable(buff, strcat(dbuff, " array"), arrSize * sizeof(int), "NULL");
                }
                else
                {
                    // identifier declaration
                    insertSymbolTable(buff, dbuff, sizeof(int), "NULL");
                    fseek(fptr, -1, SEEK_CUR);
                    col--;
                }
            }
            if (c == ';')
            {
                memset(dbuff, 0, 100);
                flag = 0;
            }
            strcpy(newToken->lexemeName, "id");
            memset(buff, 0, 100);
        }
    }
    else if (isdigit(c))
    {
        newToken->row = row;
        newToken->col = col;
        int i = 0;
        do
        {
            buff[i++] = c;
            c = fgetc(fptr);
            col++;
        } while (isdigit(c));
        fseek(fptr, -1, SEEK_CUR);
        col--;
        buff[i] = '\0';
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
    else if (c == '+' || c == '-' || c == '*' || c == '/')
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
            strcpy(newToken->lexemeName, buff);
            memset(buff, 0, 100);
        }
        else
        {
            buff[i - 1] = '\0';
            fseek(fptr, -1, SEEK_CUR);
            col--;
            strcpy(newToken->lexemeName, buff);
            memset(buff, 0, 100);
        }
    }
    else if (c == '>' || c == '<' || c == '=')
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
            strcpy(newToken->lexemeName, buff);
            memset(buff, 0, 100);
        }
        else
        {
            buff[i - 1] = '\0';
            fseek(fptr, -1, SEEK_CUR);
            col--;
            strcpy(newToken->lexemeName, buff);
            memset(buff, 0, 100);
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
        newToken = getNextToken(fptr);
        if (!newToken)
            break;
        printf("<%s, %d, %d>\n", newToken->lexemeName, newToken->row, newToken->col);
    }
    displaySymbolTable();
    return 0;
}
