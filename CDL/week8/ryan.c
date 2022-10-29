#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "la.c"

char *firstProgram = "main";
char *followProgram = "$";

char firstDeclaration[2][10] = {"int", "char"};
char *followDeclaration = "id";
int findfirstDeclaration(char *str)
{
    for (int i = 0; i < 2; i++)
        if (strcmp(firstDeclaration[i], str) == 0)
            return i;
    return -1;
}

char firstDataType[2][10] = {"int", "char"};
char *followDataType = "id";

char *firstIDList = "id";
char *followIDList = ";";

char *firstIDListPrime = ",";
char *followIDListPrime = ";";

char *firstAss = "id";
char *followAss = "}";

char firstAssPrime[2][10] = {"id", "NUM"};
char *followAssPrime = "}";
int findAssPrime(char *str)
{
    for (int i = 0; i < 2; i++)
        if (strcmp(firstAssPrime[i], str) == 0)
            return i;
    return -1;
}

void invalid()
{
    printf("FALIED\n");
    exit(0);
}

identifier_list_prime()
{
    t = getToken(fptr);
    printToken();
    if (strcmp(firstIDListPrime, t->tokenName) == 0)
        identifier_list();

    else if (strcmp(followIDListPrime, t->tokenName) == 0)
        return;

    else
    {
        printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\".\n", t->row, t->col, ",", ";");
        exit(0);
    }
}

void identifier_list()
{
    t = getToken(fptr);
    printToken();
    if (strcmp(t->tokenName, firstIDList) == 0)
        identifier_list_prime();
    else
    {
        printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "id");
        exit(0);
    }
}

void declarations()
{
    t = getToken(fptr);
    printToken();
    if (findfirstDeclaration(t->tokenName) != -1)
    {
        identifier_list();
        if (strcmp(";", t->tokenName) == 0)
            declarations();
        else
        {
            printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, ";");
            exit(0);
        }
    }
    else if (strcmp(followDeclaration, t->tokenName) == 0)
        return;
    else
    {
        printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\" or \"%s\".\n", t->row, t->col, "int", "char", "id");
        exit(0);
    }
}

void assign_stat_prime()
{
    t = getToken(fptr);
    printToken();
    if (findAssPrime(t->tokenName) != -1)
    {
        t = getToken(fptr);
        printToken();
        if (strcmp(";", t->tokenName) == 0)
            return;
        else
        {
            printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, ";");
            exit(0);
        }
    }
    else
    {
        printf("Error at row: %d, col: %d, expected \"%s\" or \"%s\".\n", t->row, t->col, "id", "NUM");
        exit(0);
    }
}

void assign_stat()
{
    if (strcmp(firstAss, t->tokenName) == 0)
    {
        t = getToken(fptr);
        printToken();
        if (strcmp("=", t->tokenName) == 0)
            assign_stat_prime();
        else
        {
            printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "=");
            exit(0);
        }
    }
    else
    {
        printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, firstAss);
        exit(0);
    }
}

void printToken() { printf("<%s, %d, %d>\n", t->tokenName, t->row, t->col); }

void program()
{
    t = getToken(fptr);
    printToken();
    if (strcmp(firstProgram, t->tokenName) == 0)
    {
        t = getToken(fptr);
        printToken();
        if (strcmp("(", t->tokenName) == 0)
        {
            t = getToken(fptr);
            printToken();
            if (strcmp(")", t->tokenName) == 0)
            {
                t = getToken(fptr);
                printToken();
                if (strcmp("{", t->tokenName) == 0)
                {
                    declarations();
                    assign_stat();
                    t = getToken(fptr);
                    printToken();
                    if (strcmp("}", t->tokenName) == 0)
                        return;
                    else
                    {
                        printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "}");
                        exit(0);
                    }
                }
                else
                {
                    printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "{");
                    exit(0);
                }
            }
            else
            {
                printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, ")");
                exit(0);
            }
        }
        else
        {
            printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, "(");
            exit(0);
        }
    }
    else
    {
        printf("Error at row: %d, col: %d, expected \"%s\".\n", t->row, t->col, firstProgram);
        exit(0);
    }
}

int main()
{
    for (int i = 0; i < MAX_HASH_SIZE; i++)
        hashSymbol[i] == NULL;
    printf("Enter the first file to be opened: ");
    scanf("%s", filename);
    fptr = fopen(filename, "r");
    if (!fptr)
    {
        printf("The file does not exist.\n");
        exit(0);
    }
    program();
    t = getToken(fptr);
    printToken();
    if (strcmp(t->tokenName, "$") == 0)
        printf("SUCCESS");
    else
        invalid();
    displaySymbolTable();
    fclose(fptr);
    return 0;
}