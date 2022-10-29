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
void U();
void V();
void W();

void S()
{
    U();
    V();
    W();
}

void U()
{
    if (str[idx] == '(')
    {
        idx++;
        S();
        if (str[idx] == ')')
        {
            idx++;
            return;
        }
        else
            inValid();
    }
    else if (str[idx] == 'a')
    {
        idx++;
        S();
        if (str[idx] == 'b')
        {
            idx++;
            return;
        }
        else
            inValid();
    }
    else if (str[idx] == 'd')
    {
        idx++;
        return;
    }
    else
        inValid();
}

void V()
{
    if (str[idx] == 'a')
    {
        idx++;
        V();
    }
}

void W()
{
    if (str[idx] == 'c')
    {
        idx++;
        W();
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
