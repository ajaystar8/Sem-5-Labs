#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TABLE_SIZE 100

struct token
{
    char tokenName[100];
    int row, col;
};

struct node
{
    char lexemeName[100];
    char type[100];
    int size;
    char returnType[100];
};

FILE *fptr;
char c, buff[100] = {0}, dbuff[100] = {0};
int row = 1, col = 1, flag = 0, idx = 0;
struct node SymbolTable[TABLE_SIZE];

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

void displaySymbolTable()
{
    printf("\n------SYMBOL TABLE------\n\n");
    printf("LexemeName\tType\tSize\tReturn-Type\n");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < idx; i++)
    {
        struct node temp = SymbolTable[i];
        printf("%s\t\t%s\t%d\t%s\t\n", temp.lexemeName, temp.type, temp.size, temp.returnType);
    }
}

int searchSymbolTable(char lexemeName[100])
{
    for (int i = 0; i < idx; i++)
        if (!strcmp(SymbolTable[i].lexemeName, lexemeName))
            return i;
    return 0;
}

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
                if (!strcmp(buff, "int") || !strcmp(buff, "float") || !strcmp(buff, "double") || !strcmp(buff, "char") || !strcmp(buff, "void"))
                {
                    strcpy(dbuff, buff);
                    flag = 1;
                }
                memset(buff, 0, 100);
                return newToken; // check
            }
        }
        if (j == 33)
        {
            if (flag)
            {
                c = fgetc(fptr);
                if (c == '(')
                {
                    c = fgetc(fptr);
                    if (c == ')' || isalpha(c))
                    {
                        if (!searchSymbolTable(buff))
                        {
                            struct node newNode;
                            strcpy(newNode.lexemeName, buff);
                            strcpy(newNode.type, "FUNC");
                            newNode.size = 0;
                            strcpy(newNode.returnType, dbuff);
                            SymbolTable[idx++] = newNode;
                        }
                    }
                    fseek(fptr, -2, SEEK_CUR);
                }
                else
                {
                    if (!searchSymbolTable(buff))
                    {
                        struct node newNode;
                        strcpy(newNode.lexemeName, buff);
                        strcpy(newNode.type, dbuff);
                        newNode.size = sizeof(int);
                        strcpy(newNode.returnType, "NULL");
                        SymbolTable[idx++] = newNode;
                        fseek(fptr, -1, SEEK_CUR);
                    }
                }
            }
            if (c == ';')
            {
                flag = 0;
                memset(dbuff, 0, 100);
            }
            // buffer word is an identifier
            strcpy(newToken->tokenName, "id");
            memset(buff, 0, 100);
        }
    }
    // 2) Handle Numbers
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
        strcpy(newToken->tokenName, "NUM");
        memset(buff, 0, 100);
    }
    // 3) Handle Symbols
    else if (findSymbol(c) != -1)
    {
        buff[0] = c;
        buff[1] = '\0';
        strcpy(newToken->tokenName, buff);
        newToken->row = row;
        newToken->col = col;
        memset(buff, 0, 100);
    }
    // 4) Handle String Literals
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
        strcpy(newToken->tokenName, buff);
        memset(buff, 0, 100);
    }
    // 5) Handle Operators
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
            strcpy(newToken->tokenName, buff);
            memset(buff, 0, 100);
        }
        else
        {
            buff[i - 1] = '\0';
            fseek(fptr, -1, SEEK_CUR);
            strcpy(newToken->tokenName, buff);
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
            strcpy(newToken->tokenName, buff);
            memset(buff, 0, 100);
        }
        else
        {
            buff[i - 1] = '\0';
            fseek(fptr, -1, SEEK_CUR);
            strcpy(newToken->tokenName, buff);
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
        newToken = getNextToken();
        if (!newToken)
            break;
        printf("<%s, %d, %d>\n", newToken->tokenName, newToken->row, newToken->col);
    }
    displaySymbolTable();
    return 0;
}