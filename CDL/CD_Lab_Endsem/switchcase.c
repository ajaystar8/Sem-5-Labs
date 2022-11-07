#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "last.c"

struct token *t;

void switch_stmt();
void case_stmts();
void case_stmts_prime();
void case_stmt();
void stmt_list();
void stmt();
void expn();
void op();

char *firstswitch_stmt = "switch";

char firstcase_stmts[2][10] = {"case", "default"};
int findfirstcase_stmts(char *str)
{
    for (int i = 0; i < 2; i++)
        if (!strcmp(firstcase_stmts[i], str))
            return i;
    return -1;
}

char firstcase_stmts_prime[2][10] = {"case", "default"};
char *followcase_stmts_prime = "}";
int findfirstcase_stmts_prime(char *str)
{
    for (int i = 0; i < 2; i++)
        if (!strcmp(firstcase_stmts_prime[i], str))
            return i;
    return -1;
}

char firstcase_stmt[2][10] = {"case", "default"};
int findfirstcase_stmt(char *str)
{
    for (int i = 0; i < 2; i++)
        if (!strcmp(firstcase_stmt[i], str))
            return i;
    return -1;
}

char *firststmt_list = "ID";
char followstmt_list[3][10] = {"case", "default", "}"};
int findfollowstmt_list(char *str)
{
    for (int i = 0; i < 3; i++)
        if (!strcmp(followstmt_list[i], str))
            return i;
    return -1;
}

char *firststmt = "ID";

char *firstexpn = "ID";

char firstop[4][10] = {"+", "-", "*", "/"};
int findfirstop(char *str)
{
    for (int i = 0; i < 4; i++)
        if (!strcmp(firstop[i], str))
            return i;
    return -1;
}

void printToken(struct token *t) { printf("< %s, %d, %d >\n", t->lexemeName, t->row, t->col); }

void switch_stmt()
{
    t = getNextToken(fptr);
    printToken(t);
    if (!strcmp(t->lexemeName, "switch"))
    {
        t = getNextToken(fptr);
        printToken(t);
        if (!strcmp(t->lexemeName, "("))
        {
            t = getNextToken(fptr);
            printToken(t);
            if (!strcmp(t->lexemeName, "ID"))
            {
                t = getNextToken(fptr);
                printToken(t);
                if (!strcmp(t->lexemeName, ")"))
                {
                    t = getNextToken(fptr);
                    printToken(t);
                    if (!strcmp(t->lexemeName, "{"))
                    {
                        case_stmts();
                        // t = getNextToken(fptr);
                        // printToken(t);
                        if (!strcmp(t->lexemeName, "}"))
                        {
                            t = getNextToken(fptr);
                            printToken(t);
                            return;
                        }
                        else
                        {
                            printf("Error: Expected %s at row %d col %d. Found %s\n", "}", t->row, t->col, t->lexemeName);
                            exit(0);
                        }
                    }
                    else
                    {
                        printf("Error: Expected %s at row %d col %d. Found %s\n", "{", t->row, t->col, t->lexemeName);
                        exit(0);
                    }
                }
                else
                {
                    printf("Error: Expected %s at row %d col %d. Found %s\n", ")", t->row, t->col, t->lexemeName);
                    exit(0);
                }
            }
            else
            {
                printf("Error: Expected %s at row %d col %d. Found %s\n", "ID", t->row, t->col, t->lexemeName);
                exit(0);
            }
        }
        else
        {
            printf("Error: Expected %s at row %d col %d. Found %s\n", "(", t->row, t->col, t->lexemeName);
            exit(0);
        }
    }
    else
    {
        printf("Error: Expected %s at row %d col %d. Found %s\n", "switch", t->row, t->col, t->lexemeName);
        exit(0);
    }
}

void case_stmts()
{
    t = getNextToken(fptr);
    printToken(t);
    if (findfirstcase_stmts(t->lexemeName) != -1)
    {
        case_stmt();        // dont call
        case_stmts_prime(); // call
    }
    else
    {
        printf("Error: Expected %s at row %d col %d. Found %s\n", "case or default", t->row, t->col, t->lexemeName);
        exit(0);
    }
}

void case_stmts_prime()
{
    // t = getNextToken(fptr);
    // printToken(t);
    if (findfirstcase_stmts(t->lexemeName) != -1)
        case_stmts();
    else if (!strcmp(t->lexemeName, followcase_stmts_prime))
        return;
    else
    {
        printf("Error: Expected %s at row %d col %d. Found %s\n", "case or default or }", t->row, t->col, t->lexemeName);
        exit(0);
    }
}

void case_stmt()
{
    if (!strcmp(t->lexemeName, "case"))
    {
        t = getNextToken(fptr);
        printToken(t);
        if (!strcmp(t->lexemeName, "NUM"))
        {
            t = getNextToken(fptr);
            printToken(t);
            if (!strcmp(t->lexemeName, ":"))
                stmt_list();
            else
            {
                printf("Error: Expected %s at row %d col %d. Found %s\n", ":", t->row, t->col, t->lexemeName);
                exit(0);
            }
        }
        else
        {
            printf("Error: Expected %s at row %d col %d. Found %s\n", "NUM", t->row, t->col, t->lexemeName);
            exit(0);
        }
    }
    else if (!strcmp(t->lexemeName, "default"))
    {
        t = getNextToken(fptr);
        printToken(t);
        if (!strcmp(t->lexemeName, ":"))
            stmt_list();
        else
        {
            printf("Error: Expected %s at row %d col %d. Found %s\n", ":", t->row, t->col, t->lexemeName);
            exit(0);
        }
    }
    else
    {
        printf("Error: Expected %s at row %d col %d. Found %s\n", "case or default", t->row, t->col, t->lexemeName);
        exit(0);
    }
}

void stmt_list()
{
    t = getNextToken(fptr);
    printToken(t);
    if (!strcmp(t->lexemeName, "ID"))
    {
        stmt();
        stmt_list();
    }
    else if (!strcmp(t->lexemeName, "case") || !strcmp(t->lexemeName, "default") || !strcmp(t->lexemeName, "}"))
        return;
    else
    {
        printf("Error: Expected %s at row %d col %d. Found %s\n", "case or default or }", t->row, t->col, t->lexemeName);
        exit(0);
    }
}

void stmt()
{
    if (!strcmp(t->lexemeName, "ID"))
    {
        t = getNextToken(fptr);
        printToken(t);
        if (!strcmp(t->lexemeName, "="))
        {
            expn();
            t = getNextToken(fptr);
            printToken(t);
            if (!strcmp(t->lexemeName, ";"))
                return;
            else
            {
                printf("Error: Expected %s at row %d col %d. Found %s\n", ";", t->row, t->col, t->lexemeName);
                exit(0);
            }
        }
        else
        {
            printf("Error: Expected %s at row %d col %d. Found %s\n", "=", t->row, t->col, t->lexemeName);
            exit(0);
        }
    }
    else
    {
        printf("Error: Expected %s at row %d col %d. Found %s\n", "ID", t->row, t->col, t->lexemeName);
        exit(0);
    }
}

void expn()
{
    t = getNextToken(fptr);
    printToken(t);
    if (!strcmp(t->lexemeName, "ID"))
    {
        op();
        t = getNextToken(fptr);
        printToken(t);
        if (!strcmp(t->lexemeName, "ID"))
            return;
        else
        {
            printf("Error: Expected %s at row %d col %d. Found %s\n", "ID", t->row, t->col, t->lexemeName);
            exit(0);
        }
    }
    else
    {
        printf("Error: Expected %s at row %d col %d. Found %s\n", "ID", t->row, t->col, t->lexemeName);
        exit(0);
    }
}

void op()
{
    t = getNextToken(fptr);
    printToken(t);
    if (findfirstop(t->lexemeName) != -1)
        return;
    else
    {
        printf("Error: Expected %s at row %d col %d. Found %s\n", "+ or - or * or /", t->row, t->col, t->lexemeName);
        exit(0);
    }
}

int main()
{
    fptr = fopen("ip.txt", "r");
    switch_stmt();
    if (!strcmp(t->lexemeName, "$"))
        printf("Success.\n");
    else
        printf("Failure.\n");
    fclose(fptr);
    return 0;
}