#include <stdio.h>

int bursttime[5] = {40, 90, 80, 15, 100};
int priority[5] = {3, 2, 5, 1, 4};
int entrytime[5] = {0, 20, 40, 60, 80};
int consider[5] = {0, 0, 0, 0, 0};

int times[5], priors[5];
int shortest, highprior, proc;
int time = 0;

void update(int burst)
{
    time += burst;
    for (int i = 0; i < 5; i++)
        if (entrytime[i] <= time)
            consider[i] = 1;
}

void init()
{
    time = 0;
    for (int i = 0; i < 5; i++)
    {
        times[i] = bursttime[i];
        priors[i] = priority[i];
        consider[i] = 0;
    }
    update(0);
}

void FCFS()
{
    printf("\nFCFS\n");
    for (int i = 0; i < 5; i++)
        printf("T: %d  Processing %d with bursttime %d\n", time, i + 1, bursttime[i]), update(bursttime[i]);
}

void SST()
{
    shortest = 1000;
    for (int i = 0; i < 5; i++)
        if (consider[i] && times[i] < shortest)
            shortest = times[i], proc = i;
    times[proc] = 1001;
}

void SSTF()
{
    printf("\nSSTF\n");
    init();
    for (int i = 0; i < 5; i++)
    {
        SST();
        printf("T: %d  Processing %d with bursttime %d\n", time, proc + 1, shortest);
        update(shortest);
    }
}

void highpriority()
{
    highprior = 0;
    for (int i = 0; i < 5; i++)
        if (consider[i] && priors[i] > highprior)
            highprior = priors[i], proc = i;
    priors[proc] = -1;
}

void Priority()
{
    printf("\nPriority Scheduling\n");
    init();
    for (int i = 0; i < 5; i++)
    {
        highpriority();
        printf("T: %d  Processing %d with priority %d\n", time, proc + 1, highprior);
        update(bursttime[proc]);
    }
}

void RoundRobin()
{
    printf("\nRound Robin\n");
    printf("Operating with burst time = 20 units\n");
    init();
    int stop = 0;
    while (!stop)
    {
        stop = 1;
        for (int i = 0; i < 5; i++)
        {
            if (!consider[i] || times[i] <= 0)
                continue;
            stop = 0;
            printf("T: %d  Processing %d with bursttime %d leaving remaning %d\n", time, i + 1, times[i], times[i] - 10 > 0 ? times[i] - 10 : 0);
            times[i] -= 20;
            update(20);
        }
    }
}

int main()
{
    printf("\nWelcome to Shyam's short and sweet demo of CPU Scheduling Algos.\n");
    FCFS();
    SSTF();
    Priority();
    RoundRobin();
}
