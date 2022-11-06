#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lardp.c"

struct token *t;

void S();
void T();
void TPrime();

char firstS[3][10] = {"id", ">", "("};
char followS[3][10] = {"$", ",", ")"};
int findFirstS(char *tokenName)
{
    for (int i = 0; i < 3; i++)
        if (!strcmp(firstS[i], tokenName))
            return i;
    return -1;
}
int findFollowS(char *tokenName)
{
    for (int i = 0; i < 3; i++)
        if (!strcmp(firstS[i], tokenName))
            return i;
    return -1;
}

char firstT[3][10] = {"id", ">", "("};
char *followT = ")";
int findFirstT(char *tokenName)
{
    for (int i = 0; i < 3; i++)
        if (!strcmp(firstT[i], tokenName))
            return i;
    return -1;
}

char *firstTPrime = ",";
char *followTPrime = ")";

void printToken(struct token *t) { printf("<%s, %d, %d>\n", t->tokenName, t->row, t->col); }

void S()
{
    t = getNextToken(fptr);
    printToken(t);
    // printf("S: %s\n", t->tokenName);
    if (findFirstS(t->tokenName) != -1)
    {
        if (!strcmp(t->tokenName, "("))
        {
            T();
            // t = getNextToken(fptr);
            // printToken(t);
            if (!strcmp(t->tokenName, ")"))
                return;
            else
            {
                printf("Error: Expected %s\n", ")");
                exit(0);
            }
        }
        else
            return;
    }
    else
    {
        printf("Error: Expected %s\n", "a or > or (");
        exit(0);
    }
}

void T()
{
    S();
    TPrime();
}

void TPrime()
{
    t = getNextToken(fptr);
    printToken(t);
    if (!strcmp(t->tokenName, firstTPrime))
    {
        S();
        TPrime();
    }
    else if (!strcmp(t->tokenName, followTPrime))
        return;
    else
    {
        printf("Error: Expected %s\n", ", or )");
        exit(0);
    }
}

int main()
{
    fptr = fopen("ip.txt", "r");
    S();
    t = getNextToken(fptr);
    if (!strcmp(t->tokenName, "$"))
        printf("Success.\n");
    else
        printf("Failure.\n");
    // displaySymbolTable();
    fclose(fptr);
    return 0;
}