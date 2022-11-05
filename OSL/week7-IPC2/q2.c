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

struct shared_use_st
{
    char alphabet;
};

int main()
{
    int shmid, run = 1;
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;
    char alpha_to_send;

    // asking for allocation of a region of shared memory
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        printf("Shared memory allocation failed.\n");
        exit(0);
    }

    // attaching the allocated shared memory block to an address
    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1)
    {
        printf("Attachment failed.\n");
        exit(0);
    }
    printf("Memory attached at %X\n", (int)shared_memory);

    // since returned address pointer is of type void, typecast it into the required shared structure pointer
    shared_stuff = (struct shared_use_st *)shared_memory;

    printf("Enter alphabet to send: ");
    scanf("%c", &alpha_to_send);
    shared_stuff->alphabet = alpha_to_send;

    printf("\nParent process wrote to shared memory.\n");

    pid_t pid = fork();

    if (pid == 0)
    {
        printf("Inside child process.\n");
        char alphabet = shared_stuff->alphabet;
        if (alphabet == 'z')
            alphabet = 'a';
        else if (alphabet == 'Z')
            alphabet = 'A';
        else
            alphabet = (char)((int)alphabet + 1);
        shared_stuff->alphabet = alphabet;
        printf("Child process updated shared memory.\n");
    }
    else
    {
        wait(NULL);
        printf("\nInside parent process...\n");
        printf("Alphabet in shared memory: %c\n", shared_stuff->alphabet);
    }

    return 0;
}