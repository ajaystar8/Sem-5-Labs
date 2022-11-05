#include <stdio.h>
#include <stdlib.h>
#include "la.c"

struct token *t;
int bufflen = 0;

char datatype[2][20] = {"int", "char"};

void program();
void id_list();
void id_prime();
void id_double_prime();
void st_list();
void st();
void ass_stat();
void expr();
void eprime();
void simple_expr();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();
void declarations();
void data_type();
void printToken() { printf("<%s, %d, %d>\n", t->tokenName, t->row, t->col); }


void inValid()
{
    printf("-----FAILURE-----\n");
    exit(0);
}

void assign_stat()
{
    if (strcmp(t->tokenName, "id") == 0)
    {
        t = getToken(fptr);
        printToken();
        // printf("%s\n", t->tokenName);
        if (strcmp(t->tokenName, "=") == 0)
        {
            assign_stat_prime();
        }
        else
            inValid();
    }
    else
        inValid();
}

void assign_stat_prime()
{
    t = getToken(fptr);
    printToken();
    if (strcmp(t->tokenName, "id") == 0 || strcmp(t->tokenName, "NUM") == 0)
    {
        t = getToken(fptr);
        printToken();
        if (strcmp(t->tokenName, ";") == 0)
            return;
        else
            inValid();
    }
    else
        inValid();
}

void identifier_list()
{
    t = getToken(fptr);
    printToken();
    if (strcmp(t->tokenName, "id") == 0)
    {
        id_list_prime();
    }
    else
        inValid();
}

void id_list_prime()
{
    t = getToken(fptr);
    printToken();
    if (strcmp(t->tokenName, ",") == 0)
    {
        identifier_list();
    }
    else
        fseek(fptr, -1, SEEK_CUR);
}

void program()
{
    t = (struct token *)malloc(sizeof(struct token));
    t = getToken(fptr);
    printToken();
    if (strcmp("main", t->tokenName) == 0)
    {
        t = getToken(fptr);
        printToken();
        if (strcmp("(", t->tokenName) == 0)
        {
            t = getToken(fptr);
            printToken();
            if (strcmp(t->tokenName, ")") == 0)
            {
                t = getToken(fptr);
                printToken();
                if (strcmp(t->tokenName, "{") == 0)
                {
                    printf("\n1.\n");
                    declarations();
                    printf("\n2.\n");
                    assign_stat();
                    printf("hello4");
                    t = getToken(fptr);
                    printToken();
                    if (strcmp(t->tokenName, "}") == 0)
                        return;
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
    printToken();
    if ((strcmp("int", t->tokenName) == 0) || (strcmp("char", t->tokenName) == 0))
    {
        identifier_list();
        t = getToken(fptr);
        printToken();
        if (strcmp(t->tokenName, ";") == 0)
        {
            declarations();
            return;
        }
        else
            fseek(fptr, -1, SEEK_CUR);
    }
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