#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lardp.c"

// VARIABLES TO BE USED
struct token *t;

// FUNCTIONS TO BE CALLED
void Program();
void Declarations();
void DataType();
void IDList();
void AssignStat();
void IDListPrime();
void AssignStatPrime();

//--------STEP-1: FILL FIRST & FOLLOW SETS------------
char *firstProgram = "main";
char *followProgram = "$";

char firstDeclarations[2][10] = {"int", "char"};
char *followDeclarations = "id";
int findFirstDeclarations(char *str)
{
    for (int i = 0; i < 2; i++)
        if (!strcmp(firstDeclarations[i], str))
            return i;
    return -1;
}

char firstDataType[2][10] = {"int", "char"};
char *followDataType = "id";
int findFirstDataType(char *str)
{
    for (int i = 0; i < 2; i++)
        if (!strcmp(firstDataType[i], str))
            return i;
    return -1;
}

char *firstIDList = "id";
char *followIDList = ";";

char *firstAssignStat = "id";
char *followAssignStat = "}";

char *firstIDListPrime = ",";
char *followIDListPrime = ";";

char firstassignStatPrime[2][10] = {"id", "NUM"};
char *followAssignStatPrime = "}";
int findFirstAssignStatPrime(char *str)
{
    for (int i = 0; i < 2; i++)
        if (!strcmp(firstassignStatPrime[i], str))
            return i;
    return -1;
}
// -----------------STEP-1 ENDS--------------------------

// -----------------STEP-2: MAKE FUNCTIONS-----------------
void printToken(struct token *t) { printf("<%s, %d, %d>\n", t->tokenName, t->row, t->col); }

void Program()
{
    t = getNextToken(fptr);
    printToken(t);
    if (!strcmp(t->tokenName, firstProgram))
    {
        t = getNextToken(fptr);
        printToken(t);
        if (!strcmp(t->tokenName, "("))
        {
            t = getNextToken(fptr);
            printToken(t);
            if (!strcmp(t->tokenName, ")"))
            {
                t = getNextToken(fptr);
                printToken(t);
                if (!strcmp(t->tokenName, "{"))
                {
                    Declarations();
                    AssignStat();
                    t = getNextToken(fptr);
                    printToken(t);
                    if (!strcmp(t->tokenName, "}"))
                        return;
                    else
                    {
                        printf("Error: Expected %s at row: %d column: %d\n", "}", t->row, t->col);
                        exit(0);
                    }
                }
                else
                {
                    printf("Error: Expected %s at row: %d column: %d\n", "{", t->row, t->col);
                    exit(0);
                }
            }
            else
            {
                printf("Error: Expected %s at row: %d column: %d\n", ")", t->row, t->col);
                exit(0);
            }
        }
        else
        {
            printf("Error: Expected %s at row: %d column: %d\n", "(", t->row, t->col);
            exit(0);
        }
    }
    else
    {
        printf("Error: Expected %s at row: %d column: %d\n", firstProgram, t->row, t->col);
        exit(0);
    }
}

void Declarations()
{
    t = getNextToken(fptr);
    printToken(t);
    if (findFirstDeclarations(t->tokenName) != -1)
    {
        IDList();
        if (!strcmp(t->tokenName, ";"))
            Declarations();
        else
        {
            printf("Error: Expected %s at row: %d column: %d\n", ";", t->row, t->col);
            exit(0);
        }
    }
    else if (!strcmp(t->tokenName, followDeclarations))
        return;
    else
    {
        printf("Error: Expected %s at row: %d column: %d\n", "int or char or id", t->row, t->col);
        exit(0);
    }
}

void AssignStat()
{
    if (!strcmp(t->tokenName, firstAssignStat))
    {
        t = getNextToken(fptr);
        printToken(t);
        if (!strcmp(t->tokenName, "="))
            AssignStatPrime();
        else
        {
            printf("Error: Expected %s at row: %d column: %d\n", "=", t->row, t->col);
            exit(0);
        }
    }
    else
    {
        printf("Error: Expected %s at row: %d column: %d\n", firstAssignStat, t->row, t->col);
        exit(0);
    }
}

void AssignStatPrime()
{
    t = getNextToken(fptr);
    printToken(t);
    if (findFirstAssignStatPrime(t->tokenName) != -1)
    {
        t = getNextToken(fptr);
        printToken(t);
        if (!strcmp(t->tokenName, ";"))
            return;
        else
        {
            printf("Error: Expected %s at row: %d column: %d\n", ";", t->row, t->col);
            exit(0);
        }
    }
    else
    {
        printf("Error: Expected %s at row: %d column: %d\n", "id or NUM", t->row, t->col);
        exit(0);
    }
}

void IDList()
{
    t = getNextToken(fptr);
    printToken(t);
    if (!strcmp(t->tokenName, firstIDList))
        IDListPrime();
    else
    {
        printf("Error: Expected %s at row: %d column: %d\n", firstIDList, t->row, t->col);
        exit(0);
    }
}

void IDListPrime()
{
    t = getNextToken(fptr);
    printToken(t);
    if (!strcmp(t->tokenName, firstIDListPrime))
        IDList();
    else if (!strcmp(t->tokenName, followIDListPrime))
        return;
    else
    {
        printf("Error: Expected %s at row: %d column: %d\n", ", or ;", t->row, t->col);
        exit(0);
    }
}

int main()
{
    fptr = fopen("ip.txt", "r");
    Program();
    t = getNextToken(fptr);
    if (!strcmp(t->tokenName, "$"))
        printf("Success.\n");
    else
        printf("Failure.\n");
    displaySymbolTable();
    fclose(fptr);
    return 0;
}