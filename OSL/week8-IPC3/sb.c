#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;
int val;

void *barber()
{
    while (1)
    {
        while (val == 10)
        {
            printf("Wating...\n");
            sleep(1);
            sem_getvalue(&semaphore, &val);
        }
        sem_post(&semaphore);
        sem_getvalue(&semaphore, &val);
        printf("Barber finshed cutting hair of customer %d\n", val);
    }
}

void *customer()
{
    while (1)
    {
        sleep(1);
        sem_getvalue(&semaphore, &val);
        if (!val)
        {
            printf("No seats empty, customer left.\n");
            continue;
        }
        sem_wait(&semaphore);
        printf("Customer %d entered and ready.\n", val);
        sem_getvalue(&semaphore, &val);
    }
}

int main()
{
    pthread_t threads[10];
    sem_init(&semaphore, 0, 10);
    sem_getvalue(&semaphore, &val);
    pthread_create(&threads[0], 0, barber, 0);
    for (int i = 1; i < 10; i++)
        pthread_create(&threads[i], 0, customer, 0);
    for (int i = 0; i < 10; i++)
        pthread_join(threads[i], 0);
    sem_destroy(&semaphore);
}
