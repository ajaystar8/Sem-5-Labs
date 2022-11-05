#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char str[100] = {0};
int idx = 0;

void inValid()
{
    printf("-----FAILURE-----\n");
    exit(0);
}

void S();
void T();
void TPrime();

void S()
{
    if (str[idx] == 'a' || str[idx] == '>')
    {
        idx++;
        return;
    }
    else if (str[idx] == '(')
    {
        idx++;
        T();
        if (str[idx] == ')')
        {
            idx++;
            return;
        }
        else
            inValid();
    }
    else
        inValid();
}

void T()
{
    S();
    TPrime();
    return;
}

void TPrime()
{
    if (str[idx] == ',')
    {
        idx++;
        S();
        TPrime();
        return;
    }
}

int main()
{
    printf("Enter string: ");
    scanf("%s", str);
    S();
    if (str[idx] == '$')
        printf("SUCCESS.\n");
    else
        printf("FAILURE - %c\n", str[idx]);

    return 0;
}