#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define LOCATIONS 8

int incomingSequence[LOCATIONS] = {176, 79, 34, 60, 92, 11, 41, 114};
int currentHeadLocation = 50;
int accessSequence[8] = {-1};
int totalSeeks = 0;

void FCFS()
{
    for (int i = 0; i < LOCATIONS; i++)
    {
        accessSequence[i] = incomingSequence[i];
        totalSeeks += abs(incomingSequence[i] - currentHeadLocation);
        currentHeadLocation = incomingSequence[i];
    }
}

int main()
{
    FCFS();
    printf("Seek sequence is: ");
    for (int i = 0; i < LOCATIONS; i++)
        printf("%d ", accessSequence[i]);

    return 0;
}