#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

sem_t wrt;
pthread_mutex_t mutex;
int data = 1;
int num_of_readers = 0;

void *writer(void *wno)
{
    // ENTRY SECTION: acquire lock before modifying the shared data
    sem_wait(&wrt);
    // CRITICAL SECTION: modyfying data. This process has exclusive write access
    data *= 2;
    printf("Writer %d modified data to %d.\n", (*(int *)wno), data);
    // EXIT SECTION: release the lock
    sem_post(&wrt);
    return NULL;
}

void *reader(void *rno)
{
    // MODIFYING A SHARED VARIABLE: num_of_readers
    //  ENTRY SECTION: to modify the num_of_readers variable.
    pthread_mutex_lock(&mutex);
    // CRITICAL SECTION: to increment the num_of_readers variable
    num_of_readers++;
    // block the writer just once, if readers present
    if (num_of_readers == 1)
        sem_wait(&wrt);
    // EXIT SECTION: realease the lock
    pthread_mutex_unlock(&mutex);

    // Reading the data
    printf("Reader %d read data as %d.\n", (*(int *)rno), data);

    // MODIFYING A SHARED VARIABLE: num_of_readers
    // ENTRY SECTION: acquire the lock to decrement the num_of_readers variable
    pthread_mutex_lock(&mutex);
    // CRITICAL SECTION: decrement the no. of readers
    num_of_readers--;
    // unblock the writer only after all readers are done with reading the shared data
    if (num_of_readers == 0)
        sem_post(&wrt);
    // EXIT SECTION
    pthread_mutex_unlock(&mutex);
}

int main()
{
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    pthread_t readers[10], writers[10];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < 10; i++)
    {
        pthread_create(&readers[i], NULL, (void *)reader, (void *)&a[i]);
        pthread_create(&writers[i], NULL, (void *)writer, (void *)&a[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}