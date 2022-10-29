#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

struct message_str
{
    long int type;
    int data;
};

int main()
{
    int msgid, num, run = 1;

    msgid = msgget((key_t)1234, 0777 | IPC_CREAT);
    if (msgid == -1)
    {
        printf("Unsuccessful.\n");
        exit(0);
    }

    while (run)
    {
        printf("Enter a number: ");
        scanf("%d", &num);
        struct message_str my_data;
        my_data.type = 1;
        my_data.data = num;
        if (num == -1)
        {
            run = 0;
            break;
        }
        else if ((msgsnd(msgid, (void *)&my_data, sizeof(my_data), 0) == -1))
        {
            printf("Unsuccessful sending.\n");
            exit(0);
        }
    }

    return 0;
}