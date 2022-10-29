#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

// extern int errno

int main()
{
    int a = 20;
    float b = 9.3;
    char c = 'A';
    char str[] = "Ajay Rajendra Kumar";
    printf(" a = %d\n b = %f\n c = %c\n str = %s\n Hexadecimal for a = %x\n", a, b, c, str, a);
    errno = EPERM;
    printf(" Error Access Number : %m\n");
}