#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int buff[10], f = 0, r = 0;
sem_t front, rear, rsrc;

void *produce(void *param)
{
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&rear);
        sem_wait(&rsrc);
        printf("Produced item: %d\n", i);
        buff[(++r) % 10] = i;
        sleep(1);
        sem_post(&rsrc);
        sem_post(&rear);
    }
    return NULL;
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
    return NULL;
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