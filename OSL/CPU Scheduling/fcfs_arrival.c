#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int num_of_processes, processes[100] = {0}, burstTimes[100] = {0}, waitingTimes[100] = {0}, turnAroundTimes[100] = {0}, arrivalTimes[100] = {0}, completionTimes[100] = {0};

void findWaitingTime(int processes[], int burstTimes[], int waitingTimes[])
{
    int start_time[100] = {0};
    waitingTimes[0] = 0;
    start_time[0] = 0;
    for (int i = 1; i < num_of_processes; i++)
    {
        start_time[i] += burstTimes[i - 1];
        waitingTimes[i] = start_time[i] - arrivalTimes[i];
        if (waitingTimes[i] < 0)
            waitingTimes[i] = 0;
    }
}

void findTurnAroundTime(int processes[], int burstTimes[], int waitingTimes[])
{
    for (int i = 0; i < num_of_processes; i++)
        turnAroundTimes[i] = burstTimes[i] + waitingTimes[i];
}

void findCompletionTime(int processes[], int burstTimes[], int waitingTimes[])
{
    for (int i = 0; i < num_of_processes; i++)
        completionTimes[i] = turnAroundTimes[i] + arrivalTimes[i];
}

int main()
{
    int total_wait_time = 0, total_turn_around_time = 0;
    printf("Enter number of processes: ");
    scanf("%d", &num_of_processes);

    printf("Enter burst times of processes: ");
    for (int i = 0; i < num_of_processes; i++)
    {
        processes[i] = i + 1;
        scanf("%d", &burstTimes[i]);
    }

    printf("Enter arrival times of processes: ");
    for (int i = 0; i < num_of_processes; i++)
        scanf("%d", &arrivalTimes[i]);

    findWaitingTime(processes, burstTimes, waitingTimes);
    findTurnAroundTime(processes, burstTimes, waitingTimes);
    findCompletionTime(processes, burstTimes, waitingTimes);

    printf("PROCESS\t\tBURST-TIME\tARRIVAL-TIME\tWAITING-TIME\tTURN-AROUND-TIME\tCOMPLETION-TIME");
    for (int i = 0; i < num_of_processes; i++)
    {
        total_wait_time += waitingTimes[i];
        total_turn_around_time += turnAroundTimes[i];
        printf("\n %d \t\t %d \t\t %d \t\t %d \t\t %d \t\t %d\n", i + 1, burstTimes[i], arrivalTimes[i], waitingTimes[i], turnAroundTimes[i], completionTimes[i]);
    }
    printf("\n");
    float s = total_wait_time / num_of_processes;
    float t = total_turn_around_time / num_of_processes;
    printf("Average waiting time = %0.2f", s);
    printf("\n");
    printf("Average turn around time = %0.2f ", t);

    return 0;
}