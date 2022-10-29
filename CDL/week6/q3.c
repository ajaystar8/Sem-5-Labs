#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char str[100] = {0};
int idx = 0;

void S();
void A();
void APrime();
void B();

void inValid()
{
    printf("-----FAILURE-----\n");
    exit(0);
}

void S()
{
    if (str[idx] == 'a')
    {
        idx++;
        A();
        if (str[idx] == 'c')
        {
            idx++;
            B();
            if (str[idx] == 'e')
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
    else
        inValid();
}

void A()
{
    if (str[idx] == 'b')
    {
        idx++;
        APrime();
    }
    else
        inValid();
}

void APrime()
{
    if (str[idx] == 'b')
    {
        idx++;
        APrime();
    }
}

void B()
{
    if (str[idx] == 'd')
    {
        idx++;
        return;
    }
    else
        inValid();
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