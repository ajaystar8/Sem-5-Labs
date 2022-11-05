#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define NUM_OF_PROCESSES 4

int process_id[NUM_OF_PROCESSES] = {1, 2, 3, 4};
int burst_times[NUM_OF_PROCESSES] = {4, 5, 6, 7};
int arrival_time[NUM_OF_PROCESSES] = {0, 1, 2, 3};
int remaining_time[NUM_OF_PROCESSES] = {0, 1, 2, 3};
int time_quantum = 3;

int total_wait_time = 0, total_turn_around_time = 0;

int main()
{
    int limit = NUM_OF_PROCESSES;
    int total_time_taken = 0;
    int process = 0;
    int done = 0;
    printf("PROCESS\tBURST-TIME\tTURN-AROUND-TIME\tWAITING TIME\n");
    for (process = 0, total_time_taken = 0; limit != 0;)
    {
        if (remaining_time[process] <= time_quantum && remaining_time[process] > 0)
        {
            total_time_taken += remaining_time[process];
            remaining_time[process] = 0;
            done = 1;
        }
        else if (remaining_time[process] > 0)
        {
            total_time_taken += time_quantum;
            remaining_time[process] -= time_quantum;
        }
        if (remaining_time[process] == 0 && done == 1)
        {
            limit--;
            printf("%d\t\t%d\t\t%d\t\t%d\n", process + 1, burst_times[process],
                   total_time_taken - arrival_time[process],
                   total_time_taken - arrival_time[process] - burst_times[process]);

            total_wait_time += total_time_taken - arrival_time[process] - burst_times[process];
            total_turn_around_time += total_time_taken - arrival_time[process];
            done = 0;
        }
        else if (arrival_time[process] < total_time_taken)
            process++;
        if (process == limit - 1)
            process = 0;
    }

    return 0;
}