#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

// 'state' denotes if philosopher is hungry(1) or eating(0)
int state[N];
// for numbering the philosophers
int phil[N] = {0, 1, 2, 3, 4};

// SHARED DATA 'state' BEING MODIFIED: Therefore use mutex locks
sem_t mutex;
// initially assume that each philosopher didn't get a chance too eat. Therefore semaphore values will be 0
// if a philosopher finishes eating, he will increment the semaphore value
sem_t S[N];

void test(int phnum)
{
    // can eat only when philosophers on the left and right aren't eating
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING)
    {
        // entered conditional statement means, started eating, hence change state
        state[phnum] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d.\n", phnum + 1, LEFT + 1, phnum + 1);
        printf("Philosopher %d is Eating\n", phnum + 1);
        // if eaten, then broadcast that.
        sem_post(&S[phnum]);
    }
}

void take_fork(int phnum)
{
    // modifying shared data: acquire lock
    sem_wait(&mutex);
    // modify shared data
    state[phnum] = HUNGRY;
    printf("Philosopher %d is hungry.\n", phnum + 1);
    // check if he can eat(both left and right chopsticks are available or not)
    test(phnum);
    // release the lock of the shared data
    sem_post(&mutex);

    // if not able to eat, then wait
    sem_wait(&S[phnum]);
    sleep(1);
}

void put_fork(int phnum)
{
    sem_wait(&mutex);
    state[phnum] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);
    // check if left and right philosophers are hungry
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void *philosopher(void *num)
{
    while (1)
    {
        int *i = num;
        sleep(1);
        take_fork(*i);
        sleep(0);
        put_fork(*i);
    }
}

int main()
{
    int i;
    pthread_t thread_id[N];

    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0);

    for (i = 0; i < N; i++)
    {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);

    return 0;
}