#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "last.c"

void Program();
void Declarations();
void Data_Type();
void IDList();
void AssignStat();
void AssignStatPrime();
void IDListPrime();

struct token *t;

char *firstProgram = "main";

char firstDeclarations[2][10] = {"int", "char"};
char *followDeclarations = "ID";
int findFirstDeclarations(char *str)
{
    for (int i = 0; i < 2; i++)
        if (!strcmp(firstDeclarations[i], str))
            return i;
    return -1;
}

char firstDataType[2][10] = {"int", "char"};
int findFirstDataType(char *str)
{
    for (int i = 0; i < 2; i++)
        if (!strcmp(firstDataType[i], str))
            return i;
    return -1;
}

char *firstIDList = "ID";

char *firstAssignStat = "ID";

char *firstIDListPrime = ",";
char *followIDListPrime = ";";

char firstAssignStatPrime[2][10] = {"ID", "NUM"};
int findFirstAssignStatPrime(char *str)
{
    for (int i = 0; i < 2; i++)
        if (!strcmp(firstAssignStatPrime[i], str))
            return i;
    return -1;
}

void printToken(struct token *t) { printf("< %s, %d, %d >\n", t->lexemeName, t->row, t->col); }

void Program()
{
    t = getNextToken(fptr);
    printToken(t);
    if (!strcmp(t->lexemeName, firstProgram))
    {
        t = getNextToken(fptr);
        printToken(t);
        if (!strcmp(t->lexemeName, "("))
        {
            t = getNextToken(fptr);
            printToken(t);
            if (!strcmp(t->lexemeName, ")"))
            {
                t = getNextToken(fptr);
                printToken(t);
                if (!strcmp(t->lexemeName, "{"))
                {
                    Declarations();
                    AssignStat();
                    t = getNextToken(fptr);
                    printToken(t);
                    if (!strcmp(t->lexemeName, "}"))
                        return;
                    else
                    {
                        printf("Error: Expected %s at row %d col %d\n", "}", t->row, t->col);
                        exit(0);
                    }
                }
                else
                {
                    printf("Error: Expected %s at row %d col %d\n", "{", t->row, t->col);
                    exit(0);
                }
            }
            else
            {
                printf("Error: Expected %s at row %d col %d\n", ")", t->row, t->col);
                exit(0);
            }
        }
        else
        {
            printf("Error: Expected %s at row %d col %d\n", "(", t->row, t->col);
            exit(0);
        }
    }
    else
    {
        printf("Error: Expected %s at row %d col %d\n", firstProgram, t->row, t->col);
        exit(0);
    }
}

void Declarations()
{
    t = getNextToken(fptr);
    printToken(t);
    if (findFirstDeclarations(t->lexemeName) != -1)
    {
        Data_Type();
        IDList();
        if (!strcmp(t->lexemeName, ";"))
            Declarations();
        else
        {
            printf("Error: Expected %s at row %d col %d\n", ";", t->row, t->col);
            exit(0);
        }
    }
    else if (!strcmp(t->lexemeName, followDeclarations))
        return;
    else
    {
        printf("Error: Expected %s at row %d col %d\n", "int or char or id", t->row, t->col);
        exit(0);
    }
}

void Data_Type()
{
    if (findFirstDataType(t->lexemeName) != -1)
        return;
    else
    {
        printf("Error: Expected %s at row %d col %d\n", "int or char", t->row, t->col);
        exit(0);
    }
}

void IDList()
{
    t = getNextToken(fptr);
    printToken(t);
    if (!strcmp(t->lexemeName, firstIDList))
        IDListPrime();
    else
    {
        printf("Error: Expected %s at row %d col %d\n", firstIDList, t->row, t->col);
        exit(0);
    }
}

void AssignStat()
{
    if (!strcmp(t->lexemeName, firstAssignStat))
    {
        t = getNextToken(fptr);
        printToken(t);
        if (!strcmp(t->lexemeName, "="))
            AssignStatPrime();
        else
        {
            printf("Error: Expected %s at row %d col %d\n", "=", t->row, t->col);
            exit(0);
        }
    }
    else
    {
        printf("Error: Expected %s at row %d col %d\n", firstAssignStat, t->row, t->col);
        exit(0);
    }
}

void IDListPrime()
{
    t = getNextToken(fptr);
    printToken(t);
    if (!strcmp(t->lexemeName, ","))
        IDList();
    else if (!strcmp(t->lexemeName, followIDListPrime))
        return;
    else
    {
        printf("Error: Expected %s at row %d col %d\n", ", or ;", t->row, t->col);
        exit(0);
    }
}

void AssignStatPrime()
{
    t = getNextToken(fptr);
    printToken(t);
    if (findFirstAssignStatPrime(t->lexemeName) != -1)
    {
        t = getNextToken(fptr);
        printToken(t);
        if (!strcmp(t->lexemeName, ";"))
            return;
        else
        {
            printf("Error: Expected %s at row %d col %d\n", ";", t->row, t->col);
            exit(0);
        }
    }
    else
    {
        printf("Error: Expected %s at row %d col %d\n", "ID or NUM", t->row, t->col);
        exit(0);
    }
}

int main()
{
    fptr = fopen("ip.txt", "r");
    Program();
    t = getNextToken(fptr);
    if (!strcmp(t->lexemeName, "$"))
        printf("SUCCESS.\n");
    else
        printf("FAILURE.\n");
    return 0;
}