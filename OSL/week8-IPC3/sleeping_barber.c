#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t customer, barber;
// mutex 'seat' is used to control the shared variable: 'waiting_seats'
pthread_mutex_t seat;
int waiting_seats = 10;

void *barb(void *args)
{
    while (1)
    {
        // barber sleeps untill customer arrives
        sem_wait(&customer);
        // as soon as customer arrives, lock the seat for cutting
        pthread_mutex_lock(&seat);
        // since one customer is having is haircut, one free waiting seat is made available
        if (waiting_seats < 10)
            waiting_seats++;
        sleep(1);
        printf("Free waiting seats available: %d.\n", waiting_seats);
        // haircut is over and barber becomes free once again
        sem_post(&barber);
        // also, after haircut over, seat also becomes free
        pthread_mutex_unlock(&seat);
    }
}

void *cust(void *args)
{
    while (1)
    {
        // since waiting_seats can be modified, acquire the lock
        pthread_mutex_lock(&seat);
        if (waiting_seats > 0)
        {
            sleep(1);
            // customer sits down, hence decrementing the number of available waiting seats
            waiting_seats--;
            printf("Free waiting seats available: %d.\n", waiting_seats);
            // wake up barber who may be waiting for a customer
            sem_post(&customer);
            // modification of shared variable over, hence release lock
            pthread_mutex_unlock(&seat);
            // wait if barber is busy
            sem_wait(&barber);
        }
        else
            pthread_mutex_unlock(&seat);
    }
}

int main()
{
    pthread_t threads[2];
    sem_init(&barber, 0, 1);
    sem_init(&customer, 0, 1);
    pthread_mutex_init(&seat, 0);

    pthread_create(&threads[0], NULL, (void *)&barb, NULL);
    for (int i = 0; i < 10; i++)
        pthread_create(&threads[1], NULL, (void *)&cust, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    sem_destroy(&barber);
    sem_destroy(&customer);
    pthread_mutex_destroy(&seat);

    return 0;
}