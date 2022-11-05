#include <stdio.h>
#include <stdlib.h>

// Table Contents
// PROCESS-ID   BURST-TIME  PRIORITY WAITING-TIME    TURN-AROUND-TIME
int A[100][5];

int num_of_processes = 0, total_waiting_time = 0, total_turn_around_time = 0;

int main()
{
    printf("Enter number of processes: ");
    scanf("%d", &num_of_processes);

    printf("Enter burst times: ");
    for (int i = 0; i < num_of_processes; i++)
    {
        A[i][0] = i + 1;
        scanf("%d", &A[i][1]);
    }
    printf("Enter Priorities: ");
    for (int i = 0; i < num_of_processes; i++)
        scanf("%d", &A[i][2]);

    // sort the table according to priority (bubble sort used)
    for (int i = 0; i < num_of_processes - 1; i++)
    {
        for (int j = 0; j < num_of_processes - i - 1; j++)
        {
            if (A[j][2] > A[j + 1][2])
            {
                // swap Priority
                int temp = A[j][2];
                A[j][2] = A[j + 1][2];
                A[j + 1][2] = temp;

                // swap Burst Time
                temp = A[j][1];
                A[j][1] = A[j + 1][1];
                A[j + 1][1] = temp;

                // swap Process ID
                temp = A[j][0];
                A[j][0] = A[j + 1][0];
                A[j + 1][0] = temp;
            }
        }
    }

    // calculation of waiting time
    A[0][2] = 0;
    for (int i = 1; i < num_of_processes; i++)
    {
        // waiting time = sum(all processes ka Burst Time that started before the current process)
        for (int j = 0; j < i; j++)
            A[i][3] += A[j][1];
        total_waiting_time += A[i][3];
    }

    // calculation of turn around time
    for (int i = 0; i < num_of_processes; i++)
    {
        A[i][4] = A[i][3] + A[i][1];
        total_turn_around_time += A[i][4];
    }

    printf("PROCESS\t\tBURST-TIME\tPRIORITY\tWAITING-TIME\tTURN-AROUND-TIME\n");
    for (int i = 0; i < num_of_processes; i++)
    {
        for (int j = 0; j < 5; j++)
            printf("%d\t\t", A[i][j]);
        printf("\n");
    }

    float s = (float)total_waiting_time / (float)num_of_processes;
    float t = (float)total_turn_around_time / (float)num_of_processes;

    printf("\nAverage waiting time = %0.2f", s);
    printf("\n");
    printf("Average turn around time = %0.2f ", t);

    return 0;
}