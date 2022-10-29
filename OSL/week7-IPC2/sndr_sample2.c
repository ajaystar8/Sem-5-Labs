#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>

struct msg_structure
{
    long int type;
    char text[1024];
};

int main()
{
    int msg_id, run = 1;
    char buff[1024] = {0};
    struct msg_structure my_data;

    msg_id = msgget((key_t)1234, 0777 | IPC_CREAT);
    if (msg_id == -1)
    {
        printf("Message Queue creation failed.\n");
        exit(0);
    }

    while (run)
    {
        printf("Enter some text: ");
        fgets(buff, 1024, stdin);
        my_data.type = 1;
        strcpy(my_data.text, buff);
        if (msgsnd(msg_id, (void *)&my_data, 1024, 0) == -1)
        {
            printf("Failed to send message.\n");
            exit(0);
        }
        if (strstr(my_data.text, "exit"))
            run = 0;
        fflush(stdin);
    }
    if (msgctl(msg_id, IPC_RMID, 0) == -1)
    {
        printf("Failed to delete message queue.\n");
        exit(0);
    }
    printf("Message queue deleted successfully.\n");

    return 0;
}