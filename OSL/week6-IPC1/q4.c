#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num = 0;
    FILE *fout = fopen("newbinfile.bin", "wb+");
    printf("Writing binary file...\n");
    printf("Enter any 4 numbers: \n");
    for (int i = 0; i < 4; i++)
    {
        scanf("%d", &num);
        fwrite(&num, sizeof(int), 1, fout);
    }
    printf("Writing complete!\n");
    fclose(fout);
    printf("Reading binary file...\n");
    fout = fopen("newbinfile.bin", "rb");
    for (int i = 0; i < 4; i++)
    {
        fread(&num, sizeof(int), 1, fout);
        printf("%d\n", num);
    }
    fclose(fout);
    return 0;
}