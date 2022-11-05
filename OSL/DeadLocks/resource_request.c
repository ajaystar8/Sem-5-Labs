#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define PROCESSES 5
#define RESOURCES 3

int ind = 0;

int Allocated[PROCESSES][RESOURCES] = {{0, 1, 0},  // P0    // Allocation Matrix
                                       {2, 0, 0},  // P1
                                       {3, 0, 2},  // P2
                                       {2, 1, 1},  // P3
                                       {0, 0, 2}}; // P4

int Max[PROCESSES][RESOURCES] = {{7, 5, 3},  // P0    // MAX Matrix
                                 {3, 2, 2},  // P1
                                 {9, 0, 2},  // P2
                                 {2, 2, 2},  // P3
                                 {4, 3, 3}}; // P4

int Available[RESOURCES] = {3, 3, 2}; // Available Resources

int Need[PROCESSES][RESOURCES];

int visited[PROCESSES] = {0};
int safe_sequence[PROCESSES] = {-1};

int request[RESOURCES] = {1, 0, 2};
int requesting_process_no = 1;

void fillNeedMatrix()
{
    for (int i = 0; i < PROCESSES; i++)
        for (int j = 0; j < RESOURCES; j++)
            Need[i][j] = Max[i][j] - Allocated[i][j];
}

int main()
{
    fillNeedMatrix();

    for (int i = 0; i < RESOURCES; i++)
    {
        if ((request[i] > Need[requesting_process_no][i]) || request[i] > Available[i])
        {
            printf("Can't Allocate resource.\n");
            exit(0);
        }
    }

    for (int i = 0; i < RESOURCES; i++)
    {
        Allocated[requesting_process_no][i] += request[i];
        Available[i] -= request[i];
    }

    fillNeedMatrix();

    // 2 for loops are used so that we can loop back to the first process when we reach the end of the process table
    // Repeated scanning of visited process is avoided using the visited[PROCESSES] table.
    for (int i = 0; i < PROCESSES; i++)
    {
        for (int j = 0; j < PROCESSES; j++)
        {
            if (!visited[j])
            {
                int flag = 0;
                for (int k = 0; k < RESOURCES; k++)
                {
                    if (Need[j][k] > Available[k])
                    {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    // process can be executed
                    safe_sequence[ind++] = j;
                    for (int y = 0; y < RESOURCES; y++)
                        Available[y] += Allocated[j][y];
                    visited[j] = 1;
                }
            }
        }
    }

    for (int i = 0; i < PROCESSES; i++)
    {
        if (visited[i] == 0)
        {
            printf("Following system not safe.\n");
            exit(0);
        }
    }

    printf("Safe Sequence: ");
    for (int i = 0; i < PROCESSES; i++)
        printf("P%d ", safe_sequence[i]);

    return 0;
}