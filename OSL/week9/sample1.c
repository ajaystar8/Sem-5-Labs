#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
    char *some_memory;
    some_memory = (char *)malloc(1024);
    sprintf(some_memory, "hello\n");
    char *some_ptr;
    some_ptr = some_memory;
    while (1)
    {
        *some_memory = '\0';
        some_memory++;
    }

    return 0;
}