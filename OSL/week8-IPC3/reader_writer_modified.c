#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

sem_t empty, full, rsrc;
int buff[10], f = 0, r = 0;
// empty = 0 => all full
// full = 0 => all empty

void *writer()
{
    for (int i = 0; i < 10; i++)
    {
        // writer should'nt write in a full buffer
        sem_wait(&empty);
        // acquire the resource
        sem_wait(&rsrc);
        buff[(++r) % 10] = i;
        printf("Data prodcuced: %d\n", i);
        // release the resource
        sem_post(&rsrc);
        // announce that buffer is not empty now
        sem_post(&full);
    }
}

void *reader()
{
    for (int i = 0; i < 10; i++)
    {
        // reader shouln't read from an empty buffer
        sem_wait(&full);
        // acquire resource
        sem_wait(&rsrc);
        printf("Data consumed is: %d\n", buff[(++f) % 10]);
        // release resource
        sem_post(&rsrc);
        // announce that one item is read and empty space is now available in buffer
        sem_post(&empty);
    }
}

int main()
{
    sem_init(&empty, 0, 0);
    sem_init(&full, 0, 0);
    sem_init(&rsrc, 0, 1);

    pthread_t threads[2];
    pthread_create(&threads[0], NULL, &writer, NULL);
    pthread_create(&threads[1], NULL, &reader, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}