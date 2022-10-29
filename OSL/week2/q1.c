#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *const argv[])
{
    DIR *dir;
    struct dirent *ent;
    struct stat sbuf;

    if ((dir = opendir(argv[1])) == NULL)
    {
        printf("Directory can't be opened.\n");
        exit(0);
    }

    dir = opendir(argv[1]);
    while ((ent = readdir(dir)) != NULL)
    {
        // print directory name
        printf("%s\t", ent->d_name);

        // get information about the file that is read each time
        lstat(ent->d_name, &sbuf);

        if (S_ISDIR(sbuf.st_mode))
            printf("d");
        else
            printf("-");

        // finding permissions for files and directories
        sbuf.st_mode &S_IRUSR ? printf("r") : printf("-");
        sbuf.st_mode &S_IWUSR ? printf("w") : printf("-");
        sbuf.st_mode &S_IXUSR ? printf("x") : printf("-");
        sbuf.st_mode &S_IRGRP ? printf("r") : printf("-");
        sbuf.st_mode &S_IWGRP ? printf("w") : printf("-");
        sbuf.st_mode &S_IXGRP ? printf("x") : printf("-");
        sbuf.st_mode &S_IROTH ? printf("r") : printf("-");
        sbuf.st_mode &S_IWOTH ? printf("w") : printf("-");
        sbuf.st_mode &S_IXOTH ? printf("x") : printf("-");

        // print size
        printf("\t%ld", sbuf.st_size);

        // print date and time
        printf("\t%s\n", ctime(&sbuf.st_ctime));
    }

    closedir(dir);

    return 0;
}