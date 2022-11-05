#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// since 'buffer' is a shared data, therefore it has to be protected to by using a sempahore (rsrc)
int buff[10], f = 0, r = 0;
// f and r will be accessed by more than one process, therefore seperate locks are necessary for them
sem_t front, rear, rsrc;

void *produce(void *param)
{
    for (int i = 0; i < 10; i++)
    {
        // only 1 producer should update the value at the position: buff[r]
        // acquire necessary locks before performing its operations
        sem_wait(&rear);
        sem_wait(&rsrc);
        buff[(++r) % 10] = i;
        printf("Produced item: %d\n", i);
        sleep(1);
        sem_post(&rsrc);
        sem_post(&rear);
    }
}

void *consume(void *param)
{
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&front);
        sem_wait(&rsrc);
        int item = buff[(++f) % 10];
        printf("Item consumed is: %d\n", item);
        sleep(1);
        sem_post(&rsrc);
        sem_post(&front);
    }
}

int main()
{
    pthread_t t1, t2;

    sem_init(&rsrc, 0, 1);
    sem_init(&front, 0, 1);
    sem_init(&rear, 0, 10);

    pthread_create(&t1, NULL, &produce, NULL);
    pthread_create(&t2, NULL, &consume, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}