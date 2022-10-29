#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
    char *sec = "hello";
    int numSector = 10;

    FILE *disqueF = fopen("file_loc_in_pendrive", "r");

    fseek(disqueF, 10, SEEK_SET);
    fwrite(sec, 10, 1, disqueF);
    fclose(disqueF);

    return 0;
}