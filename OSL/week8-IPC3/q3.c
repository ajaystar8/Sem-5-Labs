#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t s1, s2;

void *func1(void *param)
{
    sem_wait(&s1);
    sem_wait(&s2);
    printf("Thread 1. \n");
    sem_post(&s1);
}

void *func2(void *param)
{
    sem_wait(&s2);
    sem_wait(&s1);
    printf("Thread 2. \n");
    sem_post(&s2);
}

int main()
{
    pthread_t threads[2];
    sem_init(&s1, 0, 1);
    sem_init(&s2, 0, 1);

    pthread_create(&threads[0], NULL, &func1, NULL);
    pthread_create(&threads[1], NULL, &func2, NULL);

    pthread_join(threads[0], 0);
    pthread_join(threads[1], 0);

    sem_destroy(&s1);
    sem_destroy(&s2);

    return 0;
}