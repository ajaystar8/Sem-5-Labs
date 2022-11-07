#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lap2.c"

struct token *t;

void S();
void U();
void V();
void W();

char firstS[3][10] = {"(", "a", "d"};
int findFirstS(char *str)
{
    for (int i = 0; i < 3; i++)
        if (!strcmp(str, firstS[i]))
            return i;
    return -1;
}

char firstU[3][10] = {"(", "a", "d"};
int findFirstU(char *str)
{
    for (int i = 0; i < 3; i++)
        if (!strcmp(str, firstU[i]))
            return i;
    return -1;
}

char *firstV = "a";
char followV[4][10] = {"c", "$", ")", "b"};
int findFollowV(char *str)
{
    for (int i = 0; i < 4; i++)
        if (!strcmp(str, followV[i]))
            return i;
    return -1;
}

char *firstW = "c";
char followW[3][10] = {"$", ")", "b"};
int findFollowW(char *str)
{
    for (int i = 0; i < 3; i++)
        if (!strcmp(str, followW[i]))
            return i;
    return -1;
}

void printToken(struct token *t) { printf("< %s, %d, %d >\n", t->lexemeName, t->row, t->col); }

void S()
{
}