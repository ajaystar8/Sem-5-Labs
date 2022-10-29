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

int ispalin(int t)
{
    int arr[100], n = 0;
    while (t > 0)
    {
        int dig = t % 10;
        t /= 10;
        arr[n++] = dig;
    }
    for (int i = 0; i < n / 2; i++)
        if (arr[i] != arr[n - i - 1])
            return 0;
    return 1;
}

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
        struct message_str my_data;
        if ((msgrcv(msgid, (void *)&my_data, sizeof(my_data), 1, 0) == -1))
        {
            printf("Unsuccessful rcving.\n");
            exit(0);
        }
        if (my_data.data == -1)
            run = 0;
        else if (ispalin(my_data.data))
            printf("%d is a palindrome\n", my_data.data);
        else
            printf("%d is not a palindrome\n", my_data.data);
    }
    if (msgctl(msgid, IPC_RMID, 0) == -1)
    {
        perror("Deletion failed.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}