#include <stdio.h>
#include <stdlib.h>
#include "la.c"

struct token *t;

char datatype[2][20] = {"int", "char"};

void program();
void declarations();
void assign_stat();
void identifier_list();
void id_list_prime();
void DataType();

void inValid()
{
    printf("-----FAILURE FUNC-----\n");
    exit(0);
}

void assign_stat()
{
    return;
}

void identifier_list()
{
    t = getToken(fptr);
    if (strcmp(t->tokenName, "id") == 0)
    {
        id_list_prime();
    }
    else
    {
        printf("hello.\n");
        inValid();
    }
}

void id_list_prime()
{
    t = getToken(fptr);
    if (strcmp(t->tokenName, ",") == 0)
    {
        identifier_list();
    }
    else
        fseek(fptr, -1, SEEK_CUR);
}

void program()
{
    t = (struct token *)malloc(sizeof(*t));
    t = getToken(fptr);
    if (strcmp("main", t->tokenName) == 0)
    {
        t = getToken(fptr);
        if (strcmp("(", t->tokenName) == 0)
        {
            t = getToken(fptr);
            if (strcmp(t->tokenName, ")") == 0)
            {
                t = getToken(fptr);
                if (strcmp(t->tokenName, "{") == 0)
                {
                    declarations();
                    assign_stat();
                    if (strcmp(t->tokenName, "}") == 0)
                    {
                        return;
                    }
                    else
                        inValid();
                }
                else
                    inValid();
            }
            else
                inValid();
        }
        else
            inValid();
    }
    else
        inValid();
}

void declarations()
{
    // check datatype present
    t = getToken(fptr);
    if ((strcmp("int", t->tokenName) == 0) || (strcmp("char", t->tokenName) == 0))
    {
        identifier_list();
        t = getToken(fptr);
        if (strcmp(t->tokenName, ";") == 0)
        {
            declarations();
            return;
        }
        else
        {
            printf("Here.\n");
            inValid();
        }
    }
}

int main()
{
    FILE *fptr;
    t = (struct token *)malloc(sizeof(*t));

    for (int i = 0; i < MAX_HASH_SIZE; i++)
        hashSymbol[i] = NULL;

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

    // while(1) {
    // 	t = getToken(fptr);
    // 	if(!t) break;
    // 	printf("<%s, %d, %d>\n", t->tokenName, t->row, t->col);
    // }

    displaySymbolTable();
    fclose(fptr);
    return 0;
}
