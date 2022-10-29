#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "la.c"

// global variables
struct token *t;

// Program
char *firstProgram = "main";
char *followProgram = "$";

// Declarations
char firstDeclarations[2][10] = {"int", "char"};
char *followDeclarations = "id";
int findFirstDeclaration(char *str)
{
    for (int i = 0; i < 2; i++)
        if (!strcmp(str, firstDeclarations[i]))
            return i;
    return -1;
}

// Data_Type
char firstData_Type[2][10] = {"int", "char"};
char *followData_Type = "id";
int findFirstData_Type(char *str)
{
    for (int i = 0; i < 2; i++)
        if (!strcmp(str, firstData_Type[i]))
            return i;
    return -1;
}

// Id_List
char *firstId_List = "id";
char *followId_List = ";";

// Id_List_Prime
char *firstId_List_Prime = ",";
char *followId_List_Prime = ";";

// Assign_Stat
char *firstAssign_Stat = "id";
char *followAssign_Stat = "}";

// Assign_Stat_Prime
char firstAssign_Stat_Prime[2][10] = {"id", "NUM"};
char *followAssign_Stat_Prime = "}";
int findFirstAssign_Stat_Prime(char *str)
{
    for (int i = 0; i < 2; i++)
        if (!strcmp(str, firstAssign_Stat_Prime[i]))
            return i;
    return -1;
}

void inValid()
{
    printf("FAILED.\n");
    exit(0);
}

void printToken() { printf("<%s, %d, %d>\n", t->tokenName, t->row, t->col); }

void Program()
{
    t = (struct token *)malloc(sizeof(struct node));
    t = getToken(fptr);
}

int main()
{
    t = (struct token *)malloc(sizeof(*t));

    for (int i = 0; i < MAX_HASH_SIZE; i++)
        hashSymbol[i] == NULL;

    // printf("Enter the first file to be opened: ");
    // scanf("%s", filename);

    fptr = fopen("rf1.txt", "r");
    if (!fptr)
    {
        printf("The file does not exist.\n");
        exit(0);
    }

    program();
    t = getToken(fptr);
    if (strcmp(t->tokenName, "$") == 0)
        printf("SUCCESS.\n");
    else
        printf("FAILURE.\n");
    displaySymbolTable();
    fclose(fptr);

    return 0;
}